// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreBarrier.generated.h"

class UWormDetectorComponent;
class AWorm;
class UCapsuleComponent;
class UTextRenderComponent;

UCLASS()
class BOOKWORM_API AScoreBarrier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreBarrier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	int ScoreRequired = 100;

	UPROPERTY(EditDefaultsOnly)
	UWormDetectorComponent* Detector;

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* Collision;
	UPROPERTY(EditDefaultsOnly)
	UTextRenderComponent* RequiredText;

private:
	UFUNCTION()
	void CompareScore(int NewScore);
	UFUNCTION()
	void UnlockBarrier();
	UFUNCTION()
	void ReverseWorm(AWorm* Worm);

	UPROPERTY()
	bool IsUnlocked = false;
};
