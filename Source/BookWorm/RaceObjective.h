// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "RaceCheckpoint.h"
#include "RaceObjective.generated.h"

/**
 * 
 */
UCLASS()
class BOOKWORM_API ARaceObjective : public AObjective
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void SetupCheckpoints();
	UFUNCTION()
	void StartRace();
	
public:
	UPROPERTY(EditAnywhere)
	TArray<ARaceCheckpoint*> Checkpoints;

private:
	UFUNCTION()
	void ProgressCheckpoint();

	UPROPERTY()
	int CurrentCheckpointIndex = 0;
};
