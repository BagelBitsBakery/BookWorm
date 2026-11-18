// Fill out your copyright notice in the Description page of Project Settings.


#include "WormDroneCamera.h"
#include "Kismet/KismetMathLibrary.h"

AWormDroneCamera::AWormDroneCamera()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWormDroneCamera::BeginPlay()
{
	// :)
	Super::BeginPlay();

}

//Used so the camera doesn't go underground, using raycasts
void AWormDroneCamera::StayAboveGround()
{
	//Creating The Raycast
	FHitResult OutHit = FHitResult();
	FVector ActorPos = GetActorLocation();
	FVector Start = ActorPos + FVector(0.f, 0.f, 150);
	FVector End = ActorPos - FVector(0.f,0.f,DistanceFromGround);
	FCollisionQueryParams Params;
	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Camera, Params);
	if (OutHit.bBlockingHit){
		SetActorLocation(OutHit.ImpactPoint + FVector(0.f,0.f,DistanceFromGround));
	}
}

void AWormDroneCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	//Looking at the actor
	FVector Forward = FollowActor->GetActorLocation() - GetActorLocation();
	FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(Forward, FVector::UpVector);
	Rot.Pitch += FMath::Clamp(FollowActor->GetActorForwardVector().Z,0.0,1.0) * 10.f;
	Rot.Pitch += 15.f;
	SetActorRotation(Rot);

	//Moving towards the actor
	//Getting the direction
	FVector Pos = GetActorLocation();
	FVector ActorForward = FollowActor->GetActorForwardVector() * -1.f;
	FVector Backward = FVector(ActorForward.X, ActorForward.Y, 0.f).GetSafeNormal();
	FVector HorzOffset = Backward * Offset.X;
	HorzOffset.Z = Offset.Y;
	FVector OffsetPosition = FollowActor->GetActorLocation() + HorzOffset;
	Forward = (OffsetPosition) - GetActorLocation();
	//Deciding the flyspeed
	float Distance = FVector::Distance(GetActorLocation(), OffsetPosition);
	float LowerValue = FMath::Clamp(Distance / CloseFade, 0.f, 1.0);
	float Speed = FMath::Lerp(0.f,FlySpeed,LowerValue);
	if (Speed < 10.f) {
		StayAboveGround();
		return;
	}
	//Updating the position
	Pos += Forward.GetSafeNormal() * Speed * DeltaTime;
	SetActorLocation(Pos);
	StayAboveGround();
}

void AWormDroneCamera::InitCamPos()
{
	//Getting the direction
	FVector Pos = GetActorLocation();
	FVector ActorForward = FollowActor->GetActorForwardVector() * -1.f;
	FVector Backward = FVector(ActorForward.X, ActorForward.Y, 0.f).GetSafeNormal();
	FVector HorzOffset = Backward * Offset.X;
	HorzOffset.Z = Offset.Y;
	FVector OffsetPosition = FollowActor->GetActorLocation() + HorzOffset;
	SetActorLocation(OffsetPosition);

	////Looking at the actor
	FVector Forward = FollowActor->GetActorLocation() - GetActorLocation();
	FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(Forward, FVector::UpVector);
	SetActorRotation(Rot);
}
