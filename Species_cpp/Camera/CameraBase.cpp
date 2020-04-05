// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraBase.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/GameViewportClient.h"

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
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
}

// Called every frame
void ACameraBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACameraBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Right", this, &ACameraBase::HandleYawInput);
	PlayerInputComponent->BindAxis("Up", this, &ACameraBase::HandlePicthInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACameraBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACameraBase::MoveRight);
	
	PlayerInputComponent->BindAction("ChangeCameraMode", IE_Pressed, this, &ACameraBase::HandleChangingCameraMode);
	//PlayerInputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ACameraBase::ResetLeftClick);
}

void ACameraBase::HandleChangingCameraMode()
{
	cameraIsFree = !cameraIsFree;
	UGameViewportClient* GVC = GetWorld()->GetGameViewport();
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (cameraIsFree)
	{
		PC->bShowMouseCursor = false;
		GVC->SetMouseLockMode(EMouseLockMode::LockAlways);
	}
	else
	{
		PC->bShowMouseCursor = true;
		GVC->SetMouseLockMode(EMouseLockMode::DoNotLock);
	}

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


void ACameraBase::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		APawn::AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACameraBase::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		APawn::AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACameraBase::ResetLeftClick()
{
//	GetWorld()->GetGameViewport()->SetCaptureMouseOnClick(EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
}
