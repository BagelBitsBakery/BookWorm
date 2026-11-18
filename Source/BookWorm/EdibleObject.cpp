// Fill out your copyright notice in the Description page of Project Settings.


#include "EdibleObject.h"
#include "WormDetectorComponent.h"

// Sets default values
AEdibleObject::AEdibleObject()
{
	PrimaryActorTick.bCanEverTick = true;

	//setting up child components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Detector = CreateDefaultSubobject<UWormDetectorComponent>(TEXT("Detection"));
}

// Called when the game starts or when spawned
void AEdibleObject::BeginPlay()
{
	Super::BeginPlay();
	Detector->OnWormDetected.AddDynamic(this, &AEdibleObject::Eat);
}

//Called when worm detector detects worm
void AEdibleObject::Eat()
{
	EatEffect();
	Destroy();
	OnEaten.Broadcast();
}

//KEEP EMPTY IN THIS CLASS
void AEdibleObject::EatEffect()
{
}



