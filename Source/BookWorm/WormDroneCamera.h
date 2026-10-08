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

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	AActor* FollowActor;

	UPROPERTY()
	float FlySpeed = 400.f;
	
};
