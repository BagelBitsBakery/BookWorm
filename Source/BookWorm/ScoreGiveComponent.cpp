// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreGiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WormMode.h"

// Sets default values for this component's properties
UScoreGiveComponent::UScoreGiveComponent()
{

}


// Called when the game starts
void UScoreGiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UScoreGiveComponent::GiveScore()
{
	AWormMode* WormMode = Cast<AWormMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(WormMode)) {
		return;
	}
	WormMode->AlterScore(ScoreToGive);
}

