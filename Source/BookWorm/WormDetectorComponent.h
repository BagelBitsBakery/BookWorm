// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "WormDetectorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOOKWORM_API UWormDetectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWormDetectorComponent();

	UPROPERTY()
	UShapeComponent* ShapeForDetection;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWormDetected);
	UPROPERTY(BlueprintAssignable)
	FOnWormDetected OnWormDetected;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	FComponentReference ComponentRef;
};
