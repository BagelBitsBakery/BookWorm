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

	UFUNCTION()
	void StayAboveGround();

public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void InitCamPos();

	UPROPERTY()
	APawn* FollowActor;

	UPROPERTY()
	float FlySpeed = 1200.f;
	UPROPERTY()
	FVector2D Offset = FVector2D(1000.f, 100.f);
	UPROPERTY()
	float CloseFade = 1000.f;
	UPROPERTY()
	float DistanceFromGround = 250;
	
};
