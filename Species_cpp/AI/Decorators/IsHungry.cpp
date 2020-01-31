// Fill out your copyright notice in the Description page of Project Settings.


#include "IsHungry.h"
#include "AIController.h"

void UIsHungry::OnGameplayTaskActivated(UGameplayTask & Task)
{
}

void UIsHungry::OnGameplayTaskDeactivated(UGameplayTask & Task)
{
}

bool UIsHungry::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{

	AAI_Character_0* ownerRef = Cast<AAI_Character_0>(OwnerComp.GetAIOwner()->GetPawn());

	Species_Data *holder = ownerRef->GetMetabolicData();

	if (*holder->m_piHunger >= holder->GetMaxHungerBeforeNeedingToEat()) 
	{
		holder->m_bisHungry = true;
		return true;
	}
	else if (holder->m_bisHungry)
	{
		if (*holder->m_piHunger >= holder->GetOptimalHungerReduction())
		{
			return true;
		}
		else
		{
			holder->m_bisHungry = false;
			return false;
		}
	}
	else
	{
		return false;
	}
}
