// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MakeChild.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPECIES_CPP_API UMakeChild : public UBTTaskNode
{
	GENERATED_BODY()

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesArray;

	UMakeChild();

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
