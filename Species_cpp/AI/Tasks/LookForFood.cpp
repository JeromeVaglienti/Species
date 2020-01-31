// Fill out your copyright notice in the Description page of Project Settings.


#include "LookForFood.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

void ULookForFood::OnGameplayTaskActivated(UGameplayTask & Task)
{
}

EBTNodeResult::Type ULookForFood::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	const APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
	TArray<AActor*> resultArray;
	TArray<AActor*> emptyArray;

	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), pawn->GetActorLocation(), 5000.0f, objectTypesArray, AFood::StaticClass(), emptyArray, resultArray))
	{
		int index = FMath::RandRange(0, resultArray.Num() - 1);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", resultArray[index]->GetActorLocation());
	}
	else
	{
		FNavLocation resultLocation;
		if (UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomReachablePointInRadius(pawn->GetActorLocation(), 4000.0f, resultLocation, NULL, 0))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", resultLocation.Location);
		}
	}

	return EBTNodeResult::Type::Succeeded;
}

ULookForFood::ULookForFood()
{
	objectTypesArray.Add(TEnumAsByte<EObjectTypeQuery>(EObjectTypeQuery::ObjectTypeQuery1));
}