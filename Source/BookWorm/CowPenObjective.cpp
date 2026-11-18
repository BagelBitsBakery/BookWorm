// Fill out your copyright notice in the Description page of Project Settings.


#include "CowPenObjective.h"
#include "Components/BoxComponent.h"

ACowPenObjective::ACowPenObjective() {
	//Creating box collision
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(RootComponent);
}

void ACowPenObjective::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACowPenObjective::BoxOverlapBegin);
}

void ACowPenObjective::BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Cow") and !ActorsInPen.Contains(OtherActor)) {
		CowEntered();
		ActorsInPen.Add(OtherActor);
	}
}

void ACowPenObjective::CowEntered()
{
	CowsEntered += 1;
	if (CowsEntered >= CowsNeeded) {
		EndObjective();
	}
	else {
		UpdateObStatus(FString::Printf(TEXT("(%i/%i)"),CowsEntered,CowsNeeded));
	}
}
