// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnvironmentLogic/Food/Food.h"
#include "TryEat.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPECIES_CPP_API UTryEat : public UBTTaskNode
{
	GENERATED_BODY()

	UTryEat();

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesArray;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
