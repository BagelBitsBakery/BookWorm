// Fill out your copyright notice in the Description page of Project Settings.


#include "EdibleObject.h"
#include "WormDetectorComponent.h"

// Sets default values
AEdibleObject::AEdibleObject()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Detector = CreateDefaultSubobject<UWormDetectorComponent>(TEXT("Detection"));
	Detector->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AEdibleObject::BeginPlay()
{
	Super::BeginPlay();
	Detector->OnWormDetected.AddDynamic(this, &AEdibleObject::Eat);
}

void AEdibleObject::Eat()
{
	EatEffect();
	Destroy();
}

void AEdibleObject::EatEffect()
{
}

