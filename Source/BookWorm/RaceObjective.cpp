// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceObjective.h"

void ARaceObjective::BeginPlay()
{
	Super::BeginPlay();
	OnObjectiveStarted.AddDynamic(this, &ARaceObjective::StartRace);

	for (ARaceCheckpoint* Checkpoint : Checkpoints) {
		Checkpoint->OnCheckpointEntered.AddDynamic(this, &ARaceObjective::ProgressCheckpoint);
	}
}

void ARaceObjective::SetupCheckpoints()
{
}

void ARaceObjective::StartRace()
{
	CurrentCheckpointIndex = 0;
	Checkpoints[CurrentCheckpointIndex]->ActivateCheckpoint();

}

void ARaceObjective::ProgressCheckpoint()
{
	Checkpoints[CurrentCheckpointIndex]->DeactivateCheckpoint();
	CurrentCheckpointIndex += 1;
	if (CurrentCheckpointIndex >= Checkpoints.Num()) {
		EndObjective();
	}
	else {
		Checkpoints[CurrentCheckpointIndex]->ActivateCheckpoint();
		UpdateObStatus(FString::Printf(TEXT("(%i/%i)"), CurrentCheckpointIndex, Checkpoints.Num()));
	}
}
