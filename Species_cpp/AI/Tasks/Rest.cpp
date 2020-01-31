// Fill out your copyright notice in the Description page of Project Settings.


#include "Rest.h"
#include "AIController.h"
#include "AI/Agents/AI_Character_0.h"
#include "BehaviorTree/BlackboardComponent.h"

URest::URest()
{
	bNotifyTick = true;
}

void URest::OnGameplayTaskActivated(UGameplayTask & Task)
{
}

EBTNodeResult::Type URest::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	const AAI_Character_0* charact = Cast<AAI_Character_0>(OwnerComp.GetAIOwner()->GetPawn());
	charact->ChangeMetabolicState(MetabolicState::resting);
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool("IsSleeping", true);
	return EBTNodeResult::InProgress;
}

void URest::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	const AAI_Character_0* charact = Cast<AAI_Character_0>(OwnerComp.GetAIOwner()->GetPawn());
	const Species_Data *data = charact->GetMetabolicData();

	if (*data->m_piEnergy >= data->GetOptimalEnergyRecovery())
	{
		charact->ChangeMetabolicState(MetabolicState::standard);
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool("IsSleeping", false);
		OwnerComp.OnTaskFinished(this, EBTNodeResult::Succeeded);
	}
}
