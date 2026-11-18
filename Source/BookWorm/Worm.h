// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Worm.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraFollowComponent;
struct FInputActionValue;
class USphereComponent;

UCLASS()
class BOOKWORM_API AWorm : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWorm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Child Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraFollowComponent* Cam;
	//The speed the worm will be accellerating at
	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 1000.f;
	//The reverse force applied to the worm when accellerating
	UPROPERTY(EditDefaultsOnly)
	float AirDrag = 750.f;

	//Input Actions and Maps
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* MoveInputMap;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* AccelerateAction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Plays an animation to look like the worm has eaten. Made to be overriden in blueprints
	UFUNCTION(BlueprintImplementableEvent)
	void EatEffect();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// More child components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* HeadMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* Sphere;

private:
	UFUNCTION()
	void MovementInputPressed(const FInputActionValue& Value);
	UFUNCTION()
	void AccelerateInputPressed(const FInputActionValue& Value);
	//Stops gravity and allows input
	UFUNCTION()
	void GoUnderground();
	//Starts gravity and halves input
	UFUNCTION()
	void GoAboveGround();
	UFUNCTION()
	//For overlap detection
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//Check to see if an actor that blocks surface channel is above them
	UFUNCTION()
	bool IsUnderSurface();
	
	//Status of if it is underground
	UPROPERTY()
	float UndergroundValue = 0.0;
	//the amount of actors with "GroundDig" tag that the worm is in
	UPROPERTY()
	int GroundsCollided = 0;
	//The amount of acceleration the worm will have, ranges from 0 to 1
	UPROPERTY()
	float ImpulseMult = 0.f;

	//References to all collided actors
	UPROPERTY()
	TArray<AActor*> ActorsInDig = {};
};
