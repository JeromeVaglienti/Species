// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/Species_Data.h"
#include "AIController.h"
#include "Components/WidgetComponent.h"
#include "Components/PrimitiveComponent.h"
#include "AI_Character_0.generated.h"


class UAgentInfoWidget;

UCLASS()
class SPECIES_CPP_API AAI_Character_0 : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AAI_Character_0();

	enum SpecificState
	{
		none,
		sleep,
		eat,
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UBlackboardComponent* m_BC_Attached;

	UFUNCTION()
	void ClickedEventHandle(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE bool isDead() { return (*m_data->m_piLife == 0); }

	void GetDataToBlackBoard(UBlackboardComponent * _pbbData);

	Species_Data* GetMetabolicData() const;

	void FeedItself(int32 value) const;

	void ChangeMetabolicState(MetabolicState _newState) const;

	void RequestAsPartner(FVector _rendezVousLocation, AAI_Character_0* _partnerRef);

	void MakeLove() const;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* widgetComponent;

	UAgentInfoWidget* widgetInfoDisplay;

private:
	//Species Statistics
	Species_Data* m_data;

	bool bIsClicked;

	//MetabolicPointer
	typedef void(AAI_Character_0::*MetabolicSignature)(float dt);
	//Array of method ptr
	MetabolicSignature *metabolicSignature;

	void MetabolicBehavior_standard(float deltaTime);

	void MetabolicBehavior_resting(float deltaTime);

	void MetabolicConstant(float deltaTime);
	
	void DieHandle();

	void SendValueToBlackBoard(SelfAwareData _SAdata) const;

};
