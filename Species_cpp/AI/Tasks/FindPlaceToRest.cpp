// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlaceToRest.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

void UFindPlaceToRest::OnGameplayTaskActivated(UGameplayTask & Task)
{
}

EBTNodeResult::Type UFindPlaceToRest::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	const APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
	FNavLocation resultLocation;
	if (UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomReachablePointInRadius(pawn->GetActorLocation(), 4000.0f, resultLocation, NULL, 0))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", resultLocation.Location);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
