// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Worm.generated.h"

class UCameraComponent;

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

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Cam;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* HeadMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
