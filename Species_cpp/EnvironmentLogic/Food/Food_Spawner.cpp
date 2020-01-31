// Fill out your copyright notice in the Description page of Project Settings.


#include "Food_Spawner.h"

// Sets default values
AFood_Spawner::AFood_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFood_Spawner::BeginPlay()
{
	Super::BeginPlay();

	m_pCurrentNavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	
	m_vActorLocation = GetActorLocation();
}

// Called every frame
void AFood_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_ftimerCount += DeltaTime;

	if (m_ftimerCount >= m_fSpawnRate)
	{
		Spawn();
		m_ftimerCount -= m_fSpawnRate;
	}

}

void AFood_Spawner::Spawn()
{
	FNavLocation result;
	if (m_pCurrentNavigationSystem->GetRandomPointInNavigableRadius(m_vActorLocation, m_fSpawnRadius, result))
	{
		int32 value = FMath::RandRange(0, m_foodPossibleTArray.Num() - 1);

		GetWorld()->SpawnActor<AFood>(m_foodPossibleTArray[value].Get(), result.Location, FRotator::ZeroRotator);
	}
}
