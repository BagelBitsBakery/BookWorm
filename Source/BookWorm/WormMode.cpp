// Fill out your copyright notice in the Description page of Project Settings.


#include "WormMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AWormMode::BeginPlay()
{
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(),WidgetClass);
	NewWidget->AddToViewport();
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
