// Fill out your copyright notice in the Description page of Project Settings.


#include "WormDroneCamera.h"
#include "Kismet/KismetMathLibrary.h"

AWormDroneCamera::AWormDroneCamera()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWormDroneCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AWormDroneCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	//Looking at the actor
	FVector Forward = FollowActor->GetActorLocation() - GetActorLocation();
	FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(Forward, FVector::UpVector);
	SetActorRotation(Rot);

	//Moving towards the actor
	FVector Pos = GetActorLocation();
	Pos += Forward.GetSafeNormal() * FlySpeed * DeltaTime;
	SetActorLocation(Pos);
}
