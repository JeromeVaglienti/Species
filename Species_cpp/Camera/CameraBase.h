// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraBase.generated.h"

UCLASS()
class SPECIES_CPP_API ACameraBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool cameraIsFree : 1;

	void HandleYawInput(float val);
	void HandlePicthInput(float val);

	void HandleChangingCameraMode();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void ResetLeftClick();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
