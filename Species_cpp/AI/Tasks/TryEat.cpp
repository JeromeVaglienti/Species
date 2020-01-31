// Fill out your copyright notice in the Description page of Project Settings.


#include "TryEat.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AI/Agents/AI_Character_0.h"

void UTryEat::OnGameplayTaskActivated(UGameplayTask & Task)
{
}

EBTNodeResult::Type UTryEat::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	const APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
	TArray<AActor*> resultArray;
	TArray<AActor*> emptyArray;

	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), pawn->GetActorLocation(), 200.0f, objectTypesArray, AFood::StaticClass(), emptyArray, resultArray))
	{
		Cast<AAI_Character_0>(pawn)->FeedItself(Cast<AFood>(resultArray[0])->ConsumeFood());
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}


UTryEat::UTryEat()
{
	objectTypesArray.Add(TEnumAsByte<EObjectTypeQuery>(EObjectTypeQuery::ObjectTypeQuery1));
}