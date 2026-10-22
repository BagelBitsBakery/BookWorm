// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceObjective.h"

ARaceObjective::ARaceObjective() {
	PrimaryActorTick.bCanEverTick = true;
	RaceTimer = CreateDefaultSubobject<UTimeTrackComponent>(TEXT("Race Timer"));
	RaceTimer->SetComponentTickEnabled(true);
	RaceTimer->AddTickPrerequisiteActor(this);
	RaceTimer->SetTickGroup(ETickingGroup::TG_DuringPhysics);
}

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
	RaceTimer->StartRaceTimer();
}

void ARaceObjective::ProgressCheckpoint()
{
	Checkpoints[CurrentCheckpointIndex]->DeactivateCheckpoint();
	CurrentCheckpointIndex += 1;
	if (CurrentCheckpointIndex >= Checkpoints.Num()) {
		RaceTimer->EndRaceTimer();
		EndObjective();
	}
	else {
		Checkpoints[CurrentCheckpointIndex]->ActivateCheckpoint();
		UpdateObStatus(FString::Printf(TEXT("(%i/%i)"), CurrentCheckpointIndex, Checkpoints.Num()));
	}
}
