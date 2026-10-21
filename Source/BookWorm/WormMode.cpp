// Fill out your copyright notice in the Description page of Project Settings.


#include "WormMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AWormMode::BeginPlay()
{
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(),ScoreWidgetClass);
	NewWidget->AddToViewport();
	UUserWidget* NewScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ObjectiveWidgetClass);
	NewScoreWidget->AddToViewport();
}

void AWormMode::AlterScore(int ScoreChange)
{
	int NewScore = Score + ScoreChange;
	SetScore(NewScore);
}

void AWormMode::SetScore(int NewScore)
{
	Score = NewScore;
	OnScoreChanged.Broadcast(NewScore);
	UE_LOG(LogTemp, Display, TEXT("Score Changed %i"), Score);
}

int AWormMode::GetScore()
{
	return Score;
}

void AWormMode::ObjectiveStarted(FName ObjectiveName)
{
	CurrentActiveObjectives.Add(ObjectiveName);
	OnObjectiveAdded.Broadcast(ObjectiveName);
}

void AWormMode::ObjectiveEnded(FName ObjectiveName)
{
	int ObjectiveIndex = CurrentActiveObjectives.Find(ObjectiveName);
	CurrentActiveObjectives.RemoveAt(ObjectiveIndex);
	OnObjectiveRemoved.Broadcast(ObjectiveIndex);
}

void AWormMode::ObjectiveStatusChanged(FName ObjectiveName, FString NewStatus)
{
	if (!CurrentActiveObjectives.Contains(ObjectiveName)) {
		return;
	}
	int ObjectiveIndex = CurrentActiveObjectives.Find(ObjectiveName);
	OnObjectiveUpdated.Broadcast(ObjectiveIndex, NewStatus);
}
