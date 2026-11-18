// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceObjective.h"

ARaceObjective::ARaceObjective() {
	PrimaryActorTick.bCanEverTick = true;
	RaceTimer = CreateDefaultSubobject<UTimeTrackComponent>(TEXT("Race Timer"));
	//Making sure the Race timer component can actually use the tick function
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
	UpdateObStatus(FString::Printf(TEXT("(%i/%i)"), 0, Checkpoints.Num()));
}

void ARaceObjective::ProgressCheckpoint()
{
	Checkpoints[CurrentCheckpointIndex]->DeactivateCheckpoint();
	CurrentCheckpointIndex += 1;
	//Checks what state the race is in
	if (CurrentCheckpointIndex >= Checkpoints.Num()) {
		//Ends the race if it is the final checkpoint
		RaceTimer->EndRaceTimer();
		//Checks to see if the player won
		if (RaceTimer->GetRaceTime() <= TimeRequired) {
			EndObjective();
		}
		else {
			IsActive = false;
			UpdateObStatus(FString("Failed, Try Again"));
		}
	}
	else {
		//Progresses checkpoints if it wasn't the last checkpoint
		Checkpoints[CurrentCheckpointIndex]->ActivateCheckpoint();
		UpdateObStatus(FString::Printf(TEXT("(%i/%i)"), CurrentCheckpointIndex, Checkpoints.Num()));
	}
}
