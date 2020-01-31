// Fill out your copyright notice in the Description page of Project Settings.


#include "LookForPartner.h"
#include "AIController.h"
#include "AI/Agents/AI_Character_0.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

ULookForPartner::ULookForPartner()
{
	objectTypesArray.Add(TEnumAsByte<EObjectTypeQuery>(EObjectTypeQuery::ObjectTypeQuery3));
}


void ULookForPartner::OnGameplayTaskActivated(UGameplayTask & Task)
{
}

EBTNodeResult::Type ULookForPartner::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	const AAI_Character_0* charact = Cast<AAI_Character_0>(OwnerComp.GetAIOwner()->GetPawn());
	TArray<AActor*> resultArray;
	TArray<AActor*> emptyArray;

	if (charact->GetMetabolicData()->m_iReproduction_ID == -1)
	{
		FVector charactPos = charact->GetActorLocation();
		if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), charactPos, 5000.0f, objectTypesArray, AAI_Character_0::StaticClass(), emptyArray, resultArray))
		{
			for (int i = 0; i < resultArray.Num(); i++)
			{
				AAI_Character_0* newPartner = Cast<AAI_Character_0>(resultArray[i]);
				if (newPartner != charact && newPartner->GetMetabolicData()->IsAvailableForReproduction())
				{
					FVector rdvLoc = charactPos + (newPartner->GetActorLocation() - charactPos) / 2.0f;

					newPartner->RequestAsPartner(rdvLoc, charact->GetMetabolicData()->m_pOwner);
					
					charact->GetMetabolicData()->m_iReproduction_ID = 0;
					OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", rdvLoc);
					charact->GetMetabolicData()->m_pPartnerRef = newPartner;

					return EBTNodeResult::Type::Succeeded;
				}
			}
		}

		FNavLocation resultLocation;
		if (UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomReachablePointInRadius(charact->GetActorLocation(), 4000.0f, resultLocation, NULL, 0))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", resultLocation.Location);
		}
	}

	return EBTNodeResult::Type::Succeeded;
}
