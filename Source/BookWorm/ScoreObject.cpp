// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreObject.h"
#include "ScoreGiveComponent.h"
#include "Worm.h"
#include "WormDetectorComponent.h"
#include "Kismet/GameplayStatics.h"

AScoreObject::AScoreObject() {
	PrimaryActorTick.bCanEverTick = true;
	ScoreGive = CreateDefaultSubobject<UScoreGiveComponent>(TEXT("Score"));
}

void AScoreObject::EatEffect()
{
	ScoreGive->GiveScore();
	AWorm* Worm = Cast<AWorm>(UGameplayStatics::GetActorOfClass(GetWorld(), AWorm::StaticClass()));
	WormGrow(Worm);
}

void AScoreObject::BeginPlay()
{
	Super::BeginPlay();
	Detector->OnWormEntered.AddDynamic(this, &AScoreObject::WormGrow);
}

void AScoreObject::WormGrow(AWorm* Worm)
{
	FVector Scale = Worm->GetActorScale3D();
	Scale += FVector(0.01);
	Worm->SetActorScale3D(Scale);
	Worm->EatEffect();
}
