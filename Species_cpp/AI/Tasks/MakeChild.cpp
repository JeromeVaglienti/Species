// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeChild.h"
#include "AIController.h"
#include "AI/Agents/AI_Character_0.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UMakeChild::UMakeChild()
{
	objectTypesArray.Add(TEnumAsByte<EObjectTypeQuery>(EObjectTypeQuery::ObjectTypeQuery3));
}

void UMakeChild::OnGameplayTaskActivated(UGameplayTask & Task)
{
}

EBTNodeResult::Type UMakeChild::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	const AAI_Character_0* charact = Cast<AAI_Character_0>(OwnerComp.GetAIOwner()->GetPawn());
	TArray<AActor*> resultArray;
	TArray<AActor*> emptyArray;
	AActor* partnerRef = charact->GetMetabolicData()->m_pPartnerRef;

	if (charact->GetMetabolicData()->m_iReproduction_ID != -1)
	{
		FVector charactPos = charact->GetActorLocation();
		if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), charactPos, 200.0f, objectTypesArray, AAI_Character_0::StaticClass(), emptyArray, resultArray))
		{
			for (int i = 0; i < resultArray.Num(); i++)
			{
				if (resultArray[i] == partnerRef)
				{
					Cast<AAI_Character_0>(resultArray[i])->MakeLove();
					charact->MakeLove();

					return EBTNodeResult::Succeeded;
				}
			}
		}

		charact->GetMetabolicData()->m_iReproduction_ID = -1;
		charact->GetMetabolicData()->m_pPartnerRef = nullptr;
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
