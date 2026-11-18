// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraFollowComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOOKWORM_API UCameraFollowComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraFollowComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//All properties below are purely to be transferred to the camera
	
	//The maximum speed the camera will move
	UPROPERTY(EditDefaultsOnly)
	float FlySpeed = 1200.f;
	//The posisional offset the camera will have from the target
	UPROPERTY(EditDefaultsOnly)
	FVector2D Offset = FVector2D(1000.f, 100.f);
	//How close to the camera needs to be to the target before it slows down
	UPROPERTY(EditDefaultsOnly)
	float CloseFade = 1000.f;
	//The distance the camera tries to be from the ground
	UPROPERTY(EditDefaultsOnly)
	float DistanceFromGround = 250;
		
};
