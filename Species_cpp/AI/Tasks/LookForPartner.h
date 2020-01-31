// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Engine/EngineTypes.h"
#include "Containers/Array.h"
#include "Containers/EnumAsByte.h"
#include "LookForPartner.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPECIES_CPP_API ULookForPartner : public UBTTaskNode
{
	GENERATED_BODY()

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesArray;

	ULookForPartner();

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
