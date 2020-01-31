// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Species_cppGameMode.h"
#include "Species_cppPlayerController.h"
#include "Species_cppCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpecies_cppGameMode::ASpecies_cppGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASpecies_cppPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}