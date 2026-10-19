// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsItem.generated.h"

class UWormDetectorComponent;
class AWorm;

UCLASS()
class BOOKWORM_API APhysicsItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void WormEntered(AWorm* Worm);

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	UWormDetectorComponent* Detector;
	UPROPERTY(EditDefaultsOnly)
	float LaunchMultiplier = 1.f;


public:	

};
