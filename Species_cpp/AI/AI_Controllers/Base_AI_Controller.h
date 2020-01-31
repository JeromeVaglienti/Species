// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Base_AI_Controller.generated.h"

/**
 * 
 */

class AAI_Character_0;

UCLASS()
class SPECIES_CPP_API ABase_AI_Controller : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	UBlackboardComponent* m_pBBComponent;

public:
	UPROPERTY(EditAnywhere)
	UBlackboardData* BlackBoardUsed;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTreeUsed;
};
