// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaceCheckpoint.generated.h"

class UWormDetectorComponent;
class USphereComponent;

UCLASS()
class BOOKWORM_API ARaceCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARaceCheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Child Components
	UPROPERTY(EditDefaultsOnly)
	UWormDetectorComponent* Detector;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Sphere;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CheckpointMesh;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CurrentMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Allows for the checkpoint to alert entrance
	UFUNCTION()
	void ActivateCheckpoint();
	//Stops checkpoint alerting entrance
	UFUNCTION()
	void DeactivateCheckpoint();
	//Called when worm detector detects the worm
	UFUNCTION()
	void CheckpointEntered();
	//Property to track if it should allow for detection
	UPROPERTY()
	bool IsCurrent = false;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckpointEntered);
	//Called when the checkpoint is active and detects the worm
	UPROPERTY()
	FOnCheckpointEntered OnCheckpointEntered;

};
