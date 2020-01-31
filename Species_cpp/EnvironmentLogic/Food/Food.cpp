// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
}

int AFood::ConsumeFood()
{
	Destroy(this);
	return nutritionalValue;
}

