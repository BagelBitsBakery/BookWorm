// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "WormDroneCamera.generated.h"

/**
 * 
 */
UCLASS()
class BOOKWORM_API AWormDroneCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	AWormDroneCamera();

protected:
	virtual void BeginPlay() override;

	//Uses a raycast to offset the camera position above the ground
	UFUNCTION()
	void StayAboveGround();

public:
	virtual void Tick(float DeltaTime) override;
	//Sets the first position for the character
	UFUNCTION()
	void InitCamPos();

	//The target actor that the camera is trying to follow
	UPROPERTY()
	APawn* FollowActor;

	//The maximum speed the camera will move
	UPROPERTY()
	float FlySpeed = 1200.f;
	//The posisional offset the camera will have from the target
	UPROPERTY()
	FVector2D Offset = FVector2D(1000.f, 100.f);
	//How close to the camera needs to be to the target before it slows down
	UPROPERTY()
	float CloseFade = 1000.f;
	//The distance the camera tries to be from the ground
	UPROPERTY()
	float DistanceFromGround = 250;
	
};
