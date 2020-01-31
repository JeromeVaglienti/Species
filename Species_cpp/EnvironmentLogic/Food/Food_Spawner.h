// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Food.h"
#include "NavigationSystem.h"
#include "Food_Spawner.generated.h"


UCLASS()
class SPECIES_CPP_API AFood_Spawner : public AActor
{
	GENERATED_BODY()

	UNavigationSystemV1* m_pCurrentNavigationSystem;
	float m_ftimerCount;
	FVector m_vActorLocation;
	void Spawn();
public:
	// Sets default values for this actor's properties
	AFood_Spawner();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Foods Spawned"))
	TArray<TSubclassOf<AFood>> m_foodPossibleTArray;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Spawn Radius", ClampMin = "5"))
	float m_fSpawnRadius = 25.0f;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Spawn Rate", ClampMin = "0.01"))
	float m_fSpawnRate = 3.0f;

};
