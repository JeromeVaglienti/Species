// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character_0.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <cstdint>
#include <cassert>
#include <iostream>
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameMode/AIGameMode.h"

// Sets default values
AAI_Character_0::AAI_Character_0()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));

	m_data = new Species_Data(Species_Type::type_0, this);

	metabolicSignature = new MetabolicSignature[MetabolicState::count];

	metabolicSignature[MetabolicState::standard] = &AAI_Character_0::MetabolicBehavior_standard;
	metabolicSignature[MetabolicState::resting] = &AAI_Character_0::MetabolicBehavior_resting;

	widgetComponent->SetupAttachment(RootComponent);

	GetCapsuleComponent()->OnClicked.AddDynamic(this, &AAI_Character_0::ClickedEventHandle);

}

// Called when the game starts or when spawned
void AAI_Character_0::BeginPlay()
{
	Super::BeginPlay();
	widgetComponent->InitWidget();
	widgetComponent->SetVisibility(false, false);

}

// Called every frame
void AAI_Character_0::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	(this->*(metabolicSignature[m_data->currentState]))(DeltaTime);

	MetabolicConstant(DeltaTime);
}

// Called to bind functionality to input
void AAI_Character_0::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAI_Character_0::ClickedEventHandle(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	widgetComponent->SetVisibility(true, false);
}

void AAI_Character_0::GetDataToBlackBoard(UBlackboardComponent * _pbbData)
{
	m_BC_Attached = _pbbData;

	vector<SelfAwareData>keys = m_data->GetSelfAwareDataList();
	vector<SelfAwareData>::iterator it;
	for (it = keys.begin(); it != keys.end(); it++)
	{
		if (m_BC_Attached->IsValidKey(m_BC_Attached->GetKeyID(it->data_name)))
		{
			SendValueToBlackBoard(*it);
		}
	}
}

Species_Data * AAI_Character_0::GetMetabolicData() const
{
	return m_data;
}

void AAI_Character_0::FeedItself(int32 value) const
{
	m_BC_Attached->SetValueAsBool("IsEating", true);
	(*m_data->m_piHunger) -= value;
	if (*m_data->m_piHunger < 0)
	{
		*m_data->m_piHunger = 0;
	}
	SendValueToBlackBoard(m_data->GetDataFromAddress(m_data->m_piHunger));
}

//Metabolics
void AAI_Character_0::MetabolicBehavior_standard(float deltaTime)
{
	//Increments Timer
	m_data->m_fTimer_Hunger += deltaTime;
	m_data->m_fTimer_Energy += deltaTime;

	//Hunger management
	if (m_data->m_fTimer_Hunger >= m_data->GetTickTimerHunger())
	{
		m_data->m_fTimer_Hunger -= m_data->GetTickTimerHunger();

		(*m_data->m_piHunger)++;
		SendValueToBlackBoard(m_data->GetDataFromAddress(m_data->m_piHunger));
	}

	//Energy management
	if (m_data->m_fTimer_Energy >= m_data->GetTickTimerEnergy())
	{
		m_data->m_fTimer_Energy -= m_data->GetTickTimerEnergy();

		(*m_data->m_piEnergy)--;
		SendValueToBlackBoard(m_data->GetDataFromAddress(m_data->m_piEnergy));
	}

}

void AAI_Character_0::MetabolicBehavior_resting(float deltaTime)
{
	m_data->m_fTimer_Hunger += deltaTime;
	m_data->m_fTimer_Energy += deltaTime;

	//Hunger management
	if (m_data->m_fTimer_Hunger >= m_data->GetTickTimerHunger())
	{
		m_data->m_fTimer_Hunger -= m_data->GetTickTimerHunger();

		(*m_data->m_piHunger)++;
		SendValueToBlackBoard(m_data->GetDataFromAddress(m_data->m_piHunger));
	}

	//Energy management
	if (m_data->m_fTimer_Energy >= m_data->GetTickTimerEnergy())
	{
		m_data->m_fTimer_Energy -= m_data->GetTickTimerEnergy();
		// gaining this time since we are resting
		(*m_data->m_piEnergy)++;
		SendValueToBlackBoard(m_data->GetDataFromAddress(m_data->m_piEnergy));
	}

}

void AAI_Character_0::MetabolicConstant(float deltaTime)
{
	//Loosing life management

	if (*m_data->m_piHunger > m_data->GetMaxHungerBeforeDamage() || *m_data->m_piEnergy < m_data->GetMinEnergyBeforeDamage())
	{
		m_data->m_fTimer_DOT += deltaTime;

		if (m_data->m_fTimer_DOT >= m_data->GetTickTimerDOT())
		{
			m_data->m_fTimer_DOT -= m_data->GetTickTimerDOT();

			(*m_data->m_piLife) -= 2;
			SendValueToBlackBoard(m_data->GetDataFromAddress(m_data->m_piLife));
		}

	}
	else
	{
		m_data->m_fTimer_DOT = 0.0f;
	}

	if (*m_data->m_piLife <= 0)
	{
		DieHandle();
		return;
	}
}

void AAI_Character_0::ChangeMetabolicState(MetabolicState _newState) const
{
	if (m_data->currentState == _newState)
	{
		return;
	}

	m_data->currentState = _newState;
	m_data->ResetTimers();
}

void AAI_Character_0::RequestAsPartner(FVector _rendezVousLocation, AAI_Character_0* _partnerRef)
{
	m_data->m_iReproduction_ID = 1;
	m_BC_Attached->SetValueAsVector("TargetLocation", _rendezVousLocation);
	m_data->m_pPartnerRef = _partnerRef;
}

void AAI_Character_0::MakeLove() const
{
	*m_data->m_piEnergy -= 60;
	*m_data->m_piHunger += 40;

	if (m_data->m_iReproduction_ID == 0)
	{
		UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), AAI_Character_0::GetClass(), NULL, m_BC_Attached->GetValueAsVector("TargetLocation"));
		AAIGameMode *ai_gm = Cast<AAIGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (ai_gm != nullptr)
		{
			ai_gm->GetStaticWidget()->addPop();
		}
	}

	m_data->m_iReproduction_ID = -1;
	m_data->m_pPartnerRef = nullptr;
}

void AAI_Character_0::DieHandle()
{
	AAIGameMode *ai_gm = Cast<AAIGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (ai_gm != nullptr)
	{
		ai_gm->GetStaticWidget()->removePop();
	}
	Destroy(this);
}

void AAI_Character_0::SendValueToBlackBoard(SelfAwareData _SAdata) const
{
	if (_SAdata.data_type == "int")
	{
		int holderValue;
		holderValue = *static_cast<int*>(_SAdata.data_ptr);
		/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (_SAdata.data_name.ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(holderValue));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("------------"));*/
		m_BC_Attached->SetValueAsInt(_SAdata.data_name, holderValue);
	}	
	else if (_SAdata.data_type == "struct FVector")
	{
		FVector holder = *static_cast<FVector*>(_SAdata.data_ptr);
		m_BC_Attached->SetValueAsVector(_SAdata.data_name, holder);
		/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, _SAdata.data_name.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, holder.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("------------"));*/
	}
}

