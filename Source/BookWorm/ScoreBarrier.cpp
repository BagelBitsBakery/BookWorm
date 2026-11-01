// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreBarrier.h"
#include "WormDetectorComponent.h"
#include "Components/CapsuleComponent.h"
#include "Worm.h"
#include "Kismet/GameplayStatics.h"
#include "WormMode.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AScoreBarrier::AScoreBarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Detector = CreateDefaultSubobject<UWormDetectorComponent>(TEXT("Detector"));
	
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Detector->ShapeForDetection = Collision;

	RequiredText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Score Text"));
	RequiredText->SetupAttachment(Collision);
	RequiredText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	RequiredText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
}

// Called when the game starts or when spawned
void AScoreBarrier::BeginPlay()
{
	Super::BeginPlay();
	
	Detector->OnWormEntered.AddDynamic(this, &AScoreBarrier::ReverseWorm);

	if (AWormMode* WormMode = Cast<AWormMode>(UGameplayStatics::GetGameMode(GetWorld()))) {
		WormMode->OnScoreChanged.AddDynamic(this, &AScoreBarrier::CompareScore);
	}

	RequiredText->SetText(FText::FromString(FString::FromInt(ScoreRequired)));
}

void AScoreBarrier::CompareScore(int NewScore)
{
	if (IsUnlocked) {
		return;
	}
	if (NewScore >= ScoreRequired) {
		UnlockBarrier();
	}
}

void AScoreBarrier::UnlockBarrier()
{
	IsUnlocked = true;
	Destroy();
}

void AScoreBarrier::ReverseWorm(AWorm* Worm)
{
	FVector WormVel = Worm->GetVelocity();
	WormVel *= -1.f;
	Worm->Sphere->SetPhysicsLinearVelocity(WormVel * 1.5);
}

