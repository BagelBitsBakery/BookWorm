// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EdibleObject.generated.h"

class UWormDetectorComponent;

UCLASS()
class BOOKWORM_API AEdibleObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEdibleObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void Eat();
	UFUNCTION()
	virtual void EatEffect();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	UWormDetectorComponent* Detector;

public:	

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEaten);
	UPROPERTY(BlueprintAssignable)
	FOnEaten OnEaten;
};
