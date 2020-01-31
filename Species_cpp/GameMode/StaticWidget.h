// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaticWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPECIES_CPP_API UStaticWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	int32 populationCount = 0;

	FORCEINLINE void addPop() { populationCount++; }
	FORCEINLINE void removePop() { populationCount--; }
	
};
