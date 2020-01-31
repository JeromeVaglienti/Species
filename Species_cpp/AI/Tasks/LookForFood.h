// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Engine/EngineTypes.h"
#include "Containers/Array.h"
#include "EnvironmentLogic/Food/Food.h"
#include "Containers/EnumAsByte.h"
#include "LookForFood.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPECIES_CPP_API ULookForFood : public UBTTaskNode
{
	GENERATED_BODY()

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesArray;

	ULookForFood();

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
