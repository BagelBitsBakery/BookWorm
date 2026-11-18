// Fill out your copyright notice in the Description page of Project Settings.


#include "EatingObjective.h"
#include "EdibleObject.h"

void AEatingObjective::Eaten()
{
	EatenAmount += 1;
	if (EatenAmount < EatingNeeded) {
		UpdateObStatus(FString::Printf(TEXT("(%i/%i)"), EatenAmount, EatingNeeded));
	}
	else {
		EndObjective();
	}
}

void AEatingObjective::BeginPlay()
{
	Super::BeginPlay();

	//Setting up edible objects
	for (AEdibleObject* Obj : OnesThatNeedEating) {
		Obj->OnEaten.AddDynamic(this, &AEatingObjective::Eaten);
	}
	EatingNeeded = OnesThatNeedEating.Num();
}
