// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_AI_Controller.h"
#include "AI/Agents/AI_Character_0.h"

void ABase_AI_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (BlackBoardUsed != nullptr)
	{
		UseBlackboard(BlackBoardUsed, m_pBBComponent);
	}


	if (BehaviorTreeUsed != nullptr)
	{
		RunBehaviorTree(BehaviorTreeUsed);
	}

	AAI_Character_0* AAIC = Cast<AAI_Character_0>(InPawn);

	if (AAIC != nullptr && m_pBBComponent != nullptr)
	{
		AAIC->GetDataToBlackBoard(m_pBBComponent);
	}
}
