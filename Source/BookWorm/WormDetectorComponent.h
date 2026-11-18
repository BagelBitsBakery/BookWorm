// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "WormDetectorComponent.generated.h"

class AWorm;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOOKWORM_API UWormDetectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWormDetectorComponent();
	//Reference to the shape used for overlapping
	UPROPERTY()
	UShapeComponent* ShapeForDetection;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWormDetected);
	//Broadcast when the worm enteres the overlap shape
	UPROPERTY(BlueprintAssignable)
	FOnWormDetected OnWormDetected;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWormEntered,AWorm*,Worm);
	//Broadcast when the worm enteres the overlap shape, passes worm as a paramter
	UPROPERTY(BlueprintAssignable)
	FOnWormEntered OnWormEntered;
	//Given a component reference to a shape, component does not work if it is not set
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	FComponentReference ComponentRef;
};
