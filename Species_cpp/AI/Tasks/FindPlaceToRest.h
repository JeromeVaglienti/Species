// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindPlaceToRest.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPECIES_CPP_API UFindPlaceToRest : public UBTTaskNode
{
	GENERATED_BODY()


	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
