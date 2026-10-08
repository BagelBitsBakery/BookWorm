// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Worm.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class BOOKWORM_API AWorm : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWorm();

private:
	UFUNCTION()
	void MovementInputPressed(FInputActionValue& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* Cam;
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* HeadMesh;
	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 1000.f;
	UPROPERTY(EditDefaultsOnly)
	float AirDrag = 750.f;

	//Input Ones
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* Map;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
