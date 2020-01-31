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

	UFUNCTION(BlueprintCallable)
	float getLifePercentage();
	
	UFUNCTION(BlueprintCallable)
	float getEnrgyPercentage();

	UFUNCTION(BlueprintCallable)
	float getHungerPercentage();
};
