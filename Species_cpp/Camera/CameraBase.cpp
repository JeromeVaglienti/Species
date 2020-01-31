// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraBase.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACameraBase::ACameraBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraBase::BeginPlay()
{
	Super::BeginPlay();
	cameraIsFree = true;
}

// Called every frame
void ACameraBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACameraBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Right", this, &ACameraBase::HandleYawInput);
	PlayerInputComponent->BindAxis("Up", this, &ACameraBase::HandlePicthInput);

	PlayerInputComponent->BindAction("ChangeCameraMode", IE_Pressed, this, &ACameraBase::HandleChangingCameraMode);

}

void ACameraBase::HandleYawInput(float val)
{
	if (cameraIsFree)
	{
		APawn::AddControllerYawInput(val);
	}
}

void ACameraBase::HandlePicthInput(float val)
{
	if (cameraIsFree)
	{
		APawn::AddControllerPitchInput(val);
	}
}

void ACameraBase::HandleChangingCameraMode()
{
	cameraIsFree = !cameraIsFree;
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	/*if (!cameraIsFree)
	{
		FInputModeUIOnly inputMode;
		PC->SetInputMode(inputMode);
	}
	else
	{
		FInputModeGameAndUI inputMode;
		PC->SetInputMode(inputMode);
	}*/
	

	PC->SetIgnoreLookInput(!cameraIsFree);
	//GetWorld()->GetFirstPlayerController()
}
