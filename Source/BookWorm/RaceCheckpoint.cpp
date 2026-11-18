// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceCheckpoint.h"
#include "Components/SphereComponent.h"
#include "WormDetectorComponent.h"

// Sets default values
ARaceCheckpoint::ARaceCheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Setting up child components
	Detector = CreateDefaultSubobject<UWormDetectorComponent>(TEXT("Detector"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Detector->ShapeForDetection = Sphere;
	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMesh"));
	CheckpointMesh->SetupAttachment(Sphere);
	CurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurrentMesh"));
	CurrentMesh->SetupAttachment(Sphere);
	//Making meshes ignore everything
	CheckpointMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CurrentMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CurrentMesh->SetVisibility(false);
}

// Called when the game starts or when spawned
void ARaceCheckpoint::BeginPlay()
{
	Super::BeginPlay();
	Detector->OnWormDetected.AddDynamic(this, &ARaceCheckpoint::CheckpointEntered);
}

// Called every frame
void ARaceCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARaceCheckpoint::ActivateCheckpoint()
{
	IsCurrent = true;
	CurrentMesh->SetVisibility(true);
}

void ARaceCheckpoint::DeactivateCheckpoint()
{
	IsCurrent = false;
	CurrentMesh->SetVisibility(false);
}

void ARaceCheckpoint::CheckpointEntered()
{
	if (!IsCurrent) return;
	OnCheckpointEntered.Broadcast();
}

