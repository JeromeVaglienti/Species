// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/HUD.h"
#include "AI/Agents/AI_Character_0.h"

void AAIGameMode::BeginPlay()
{
	Super::BeginPlay();

	statWidget = CreateWidget<UStaticWidget>(GetWorld()->GetGameInstance(), StatsWidget);
	statWidget->AddToViewport();

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_Character_0::StaticClass(), FoundActor);
	statWidget->populationCount = FoundActor.Num();
}
