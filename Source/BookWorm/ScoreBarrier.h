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

	//The score needed before the barrier disapears
	UPROPERTY(EditAnywhere)
	int ScoreRequired = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Child Components
	UPROPERTY(EditDefaultsOnly)
	UWormDetectorComponent* Detector;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* Collision;
	UPROPERTY(EditDefaultsOnly)
	UTextRenderComponent* RequiredText;

private:
	//Compares the score with the required score, unlocks if score is greater
	UFUNCTION()
	void CompareScore(int NewScore);
	//Deletes the barrier
	UFUNCTION()
	void UnlockBarrier();
	//Reverses the given worms velocity
	UFUNCTION()
	void ReverseWorm(AWorm* Worm);
	//Tracks unlock status
	UPROPERTY()
	bool IsUnlocked = false;
};
