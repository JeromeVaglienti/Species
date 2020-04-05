// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Species_cppPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Species_cppCharacter.h"
#include "Engine/World.h"

ASpecies_cppPlayerController::ASpecies_cppPlayerController()
{
	bShowMouseCursor = false;
}