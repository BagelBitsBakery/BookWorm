// Fill out your copyright notice in the Description page of Project Settings.


#include "Worm.h"
#include "Camera/CameraComponent.h"

// Sets default values
AWorm::AWorm()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head Mesh"));
	HeadMesh->SetupAttachment(RootComponent);
	HeadMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Cam->SetupAttachment(HeadMesh);
	Cam->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
}

// Called when the game starts or when spawned
void AWorm::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWorm::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

