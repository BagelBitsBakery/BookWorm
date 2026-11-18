// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "RaceCheckpoint.h"
#include "TimeTrackComponent.h"
#include "RaceObjective.generated.h"

/**
 * 
 */
UCLASS()
class BOOKWORM_API ARaceObjective : public AObjective
{
	GENERATED_BODY()
	
	ARaceObjective();

protected:
	virtual void BeginPlay() override;
	//Connects the checkpoints to the objective
	UFUNCTION()
	void SetupCheckpoints();
	//Starts the timer and activates the first checkpoint
	UFUNCTION()
	void StartRace();
	//Child components
	UPROPERTY(EditDefaultsOnly)
	UTimeTrackComponent* RaceTimer;
	
	
public:
	//The time that the player needs to be below when finishing to end the objective
	UPROPERTY(EditAnywhere)
	float TimeRequired = 30.f;
	//All checkpoints in race, checkpoints will be activated in array order
	UPROPERTY(EditAnywhere)
	TArray<ARaceCheckpoint*> Checkpoints;

private:
	//Deactivates one checkpoint and activates the next
	UFUNCTION()
	void ProgressCheckpoint();
	//Tracks the race progress
	UPROPERTY()
	int CurrentCheckpointIndex = 0;
};
