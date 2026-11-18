// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"
#include "Components/SphereComponent.h"
#include "ScoreGiveComponent.h"
#include "WormDetectorComponent.h"
#include "WormMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObjective::AObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Setting up components
	Detector = CreateDefaultSubobject<UWormDetectorComponent>(TEXT("Worm Detect"));
	EnterDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Detector->ShapeForDetection = EnterDetection;
	SetRootComponent(EnterDetection);
	ScoreGive = CreateDefaultSubobject<UScoreGiveComponent>(TEXT("ScoreGive"));
}

// Called when the game starts or when spawned
void AObjective::BeginPlay()
{
	Super::BeginPlay();
	Detector->OnWormDetected.AddDynamic(this, &AObjective::StartObjective);
}

void AObjective::StartObjective()
{
	//Cancelling if active or complete
	if (IsActive or IsComplete) return;
	IsActive = true;
	//Updating Game Mode
	if (AWormMode* Mode = Cast<AWormMode>(UGameplayStatics::GetGameMode(GetWorld()))) {
		Mode->ObjectiveStarted(ObjectiveName);
		UE_LOG(LogTemp, Display, TEXT("Objective Start Attempted"));
	}
	OnObjectiveStarted.Broadcast();
}

void AObjective::EndObjective()
{
	//Stopping if not active
	if (!IsActive or IsComplete) return;
	IsActive = true;
	IsComplete = true;
	//Updating Game Mode
	if (AWormMode* Mode = Cast<AWormMode>(UGameplayStatics::GetGameMode(GetWorld()))) {
		Mode->ObjectiveEnded(ObjectiveName);
	}
	ScoreGive->GiveScore();
	OnObjectiveEnded.Broadcast();
}

void AObjective::UpdateObStatus(FString Status)
{
	//Updating game mode
	if (AWormMode* Mode = Cast<AWormMode>(UGameplayStatics::GetGameMode(GetWorld()))) {
		Mode->ObjectiveStatusChanged(ObjectiveName,Status);
	}
}
