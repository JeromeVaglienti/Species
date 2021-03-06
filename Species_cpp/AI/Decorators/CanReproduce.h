// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "AI/Agents/AI_Character_0.h"
#include "CanReproduce.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPECIES_CPP_API UCanReproduce : public UBTDecorator
{
	GENERATED_BODY()

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
