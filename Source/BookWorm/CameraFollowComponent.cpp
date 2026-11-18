// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraFollowComponent.h"
#include "WormDroneCamera.h"

// Sets default values for this component's properties
UCameraFollowComponent::UCameraFollowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraFollowComponent::BeginPlay()
{
	Super::BeginPlay();

	//Creating a new follow camera
	AWormDroneCamera* Drone = GetWorld()->SpawnActor<AWormDroneCamera>(AWormDroneCamera::StaticClass(), GetOwner()->GetActorTransform());
	//Gets the actor owner to be used as a target
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!IsValid(Pawn)) {
		return;
	}
	Drone->FollowActor = Pawn;
	//Changing camera view to follow camera
	APlayerController* PlayerControl = Cast<APlayerController>(Pawn->GetController());
	if (IsValid(PlayerControl)) {
		PlayerControl->SetViewTarget(Drone);
	}
	//Initializing the camera
	Drone->InitCamPos();
	Drone->FlySpeed = FlySpeed;
	Drone->Offset = Offset;
	Drone->CloseFade = CloseFade;
	Drone->DistanceFromGround = DistanceFromGround;
}


// Called every frame
void UCameraFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

