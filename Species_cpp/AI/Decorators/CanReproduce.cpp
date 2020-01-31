// Fill out your copyright notice in the Description page of Project Settings.


#include "CanReproduce.h"

void UCanReproduce::OnGameplayTaskActivated(UGameplayTask & Task)
{
}

void UCanReproduce::OnGameplayTaskDeactivated(UGameplayTask & Task)
{
}

bool UCanReproduce::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	AAI_Character_0* ownerRef = Cast<AAI_Character_0>(OwnerComp.GetAIOwner()->GetPawn());

	Species_Data *holder = ownerRef->GetMetabolicData();

	return holder->CanReproduce();
}
