// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/Species_Data.h"
#include "AgentInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPECIES_CPP_API UAgentInfoWidget : public UUserWidget
{
	GENERATED_BODY()

	Species_Data* dataRef;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void getLifePercentage(float value);
	
	UFUNCTION(BlueprintImplementableEvent)
	void getEnergyPercentage(float value);

	UFUNCTION(BlueprintImplementableEvent)
	void getHungerPercentage(float value);
};
