// Fill out your copyright notice in the Description page of Project Settings.


#include "IsTired.h"
#include "AIController.h"
#include "AI/Agents/AI_Character_0.h"

void UIsTired::OnGameplayTaskActivated(UGameplayTask & Task)
{
}

void UIsTired::OnGameplayTaskDeactivated(UGameplayTask & Task)
{
}

bool UIsTired::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	const APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
	const Species_Data *data = Cast<AAI_Character_0>(pawn)->GetMetabolicData();

	return *data->m_piEnergy < data->GetMinEnergyBeforeNeedingToRest();
}
