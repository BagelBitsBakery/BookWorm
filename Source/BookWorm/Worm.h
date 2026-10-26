// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Worm.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraFollowComponent;
struct FInputActionValue;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraFollowComponent* Cam;
	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 1000.f;
	UPROPERTY(EditDefaultsOnly)
	float AirDrag = 750.f;

	//Input Ones
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* MoveInputMap;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* AccelerateAction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* HeadMesh;

private:
	UFUNCTION()
	void MovementInputPressed(const FInputActionValue& Value);
	UFUNCTION()
	void AccelerateInputPressed(const FInputActionValue& Value);
	UFUNCTION()
	void GoUnderground();
	UFUNCTION()
	void GoAboveGround();
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	bool IsUnderSurface();
	

	UPROPERTY()
	float UndergroundValue = 0.0;
	UPROPERTY()
	int GroundsCollided = 0;
	UPROPERTY()
	float ImpulseMult = 1.f;

	UPROPERTY()
	TArray<AActor*> ActorsInDig = {};
};
