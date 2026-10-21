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

	UFUNCTION()
	void ActivateCheckpoint();
	UFUNCTION()
	void DeactivateCheckpoint();
	UFUNCTION()
	void CheckpointEntered();

	UPROPERTY()
	bool IsCurrent = false;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckpointEntered);
	UPROPERTY()
	FOnCheckpointEntered OnCheckpointEntered;

};
