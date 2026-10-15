// Fill out your copyright notice in the Description page of Project Settings.


#include "WormMode.h"

void AWormMode::AlterScore(int ScoreChange)
{
	int NewScore = Score + ScoreChange;
	SetScore(NewScore);
}

void AWormMode::SetScore(int NewScore)
{
	Score = NewScore;
	OnScoreChanged.Broadcast();
	UE_LOG(LogTemp, Display, TEXT("Score Changed %i"), Score);
}

int AWormMode::GetScore()
{
	return Score;
}
