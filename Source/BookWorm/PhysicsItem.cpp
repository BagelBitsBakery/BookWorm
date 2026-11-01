// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsItem.h"
#include "WormDetectorComponent.h"
#include "Worm.h"

// Sets default values
APhysicsItem::APhysicsItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Detector = CreateDefaultSubobject<UWormDetectorComponent>(TEXT("Detector"));
}

// Called when the game starts or when spawned
void APhysicsItem::BeginPlay()
{
	Super::BeginPlay();

	Detector->OnWormEntered.AddDynamic(this, &APhysicsItem::WormEntered);
	
}

void APhysicsItem::WormEntered(AWorm* Worm)
{
	Mesh->SetSimulatePhysics(true);
	FVector WormNormal = Worm->GetVelocity().GetSafeNormal();
	float LaunchStrength = FVector::Distance(Worm->GetVelocity(), FVector::Zero());
	FVector PosNormal = (GetActorLocation() - Worm->GetActorLocation()).GetSafeNormal();
	FVector LaunchNormal = FMath::Lerp(PosNormal,WormNormal,0.5);
	FVector Launch = LaunchNormal * (LaunchStrength * LaunchMultiplier);
	Mesh->AddImpulse(Launch,FName(),true);
}

