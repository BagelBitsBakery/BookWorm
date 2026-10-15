// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreObject.h"
#include "ScoreGiveComponent.h"

AScoreObject::AScoreObject() {
	ScoreGive = CreateDefaultSubobject<UScoreGiveComponent>(TEXT("Score"));
}

void AScoreObject::EatEffect()
{
	ScoreGive->GiveScore();
}
