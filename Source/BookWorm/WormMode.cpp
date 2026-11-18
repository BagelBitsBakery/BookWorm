// Fill out your copyright notice in the Description page of Project Settings.


#include "WormMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AWormMode::AWormMode() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AWormMode::BeginPlay()
{
	//Setting up the initial UI
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(),ScoreWidgetClass);
	NewWidget->AddToViewport();
	UUserWidget* NewScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ObjectiveWidgetClass);
	NewScoreWidget->AddToViewport();
}

void AWormMode::Tick(float DeltaTime)
{
	//Slowly lowering the score multiplier
	ScoreMultiplier -= DeltaTime / 25.f;
	ScoreMultiplier = FMath::Clamp(ScoreMultiplier, 1.f, 5.f);
}

void AWormMode::AlterScore(int ScoreChange)
{
	int NewScore = Score + ScoreChange * ScoreMultiplier;
	SetScore(NewScore);
	if (ScoreChange > 0) {
		ScoreMultiplier += 0.2;
	}
}

void AWormMode::SetScore(int NewScore)
{
	Score = NewScore;
	OnScoreChanged.Broadcast(NewScore);
}

int AWormMode::GetScore()
{
	return Score;
}

void AWormMode::ObjectiveStarted(FName ObjectiveName)
{
	//Stopping the code if the objective is already going on
	if (CurrentActiveObjectives.Contains(ObjectiveName)) return;
	CurrentActiveObjectives.Add(ObjectiveName);
	OnObjectiveAdded.Broadcast(ObjectiveName);
}

void AWormMode::ObjectiveEnded(FName ObjectiveName)
{
	//Stopping the code if the objective is not already active
	if (!CurrentActiveObjectives.Contains(ObjectiveName)) return;
	//Finding the the index that the objective is in to be passed elsewhere
	int ObjectiveIndex = CurrentActiveObjectives.Find(ObjectiveName);
	CurrentActiveObjectives.RemoveAt(ObjectiveIndex);
	OnObjectiveRemoved.Broadcast(ObjectiveIndex);
}

void AWormMode::ObjectiveStatusChanged(FName ObjectiveName, FString NewStatus)
{
	//Stopping the code if the objective is not already active
	if (!CurrentActiveObjectives.Contains(ObjectiveName)) return;
	//Finding the the index that the objective is in to be passed elsewhere
	int ObjectiveIndex = CurrentActiveObjectives.Find(ObjectiveName);
	OnObjectiveUpdated.Broadcast(ObjectiveIndex, NewStatus);
}

bool AWormMode::HasObjective(FName ObjectiveName)
{
	return CurrentActiveObjectives.Contains(ObjectiveName);
}

float AWormMode::GetComboMultiplier()
{
	return floor(ScoreMultiplier * 100.f)/100.f;
}
