// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode/StaticWidget.h"
#include "AIGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPECIES_CPP_API AAIGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UStaticWidget* statWidget;

	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget>StatsWidget;

	FORCEINLINE UStaticWidget* GetStaticWidget() const { return statWidget; }
	
};
