// Fill out your copyright notice in the Description page of Project Settings.


#include "Worm.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystem.h"
#include "EnhancedInputComponent.h"

// Sets default values
AWorm::AWorm()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head Mesh"));
	HeadMesh->SetupAttachment(RootComponent);
	HeadMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	HeadMesh->SetSimulatePhysics(true);
	HeadMesh->SetEnableGravity(false);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	SpringArm->SetupAttachment(HeadMesh);
	SpringArm->bUsePawnControlRotation = true;

	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Cam->SetupAttachment(SpringArm);
	Cam->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
}

void AWorm::MovementInputPressed(FInputActionValue& Value)
{
}

// Called when the game starts or when spawned
void AWorm::BeginPlay()
{
	Super::BeginPlay();
	//redoing this bit here to see if it works now
	HeadMesh->SetSimulatePhysics(true);
	HeadMesh->SetEnableGravity(false);
}

// Called every frame
void AWorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Drag
	float VelStrength = FVector::Distance(HeadMesh->GetPhysicsLinearVelocity(), FVector::Zero());
	FVector VelNormal = HeadMesh->GetPhysicsLinearVelocity().GetSafeNormal();
	float DragStrength = (VelStrength / MoveSpeed) * AirDrag;
	VelStrength -= DragStrength * DeltaTime;
	HeadMesh->SetPhysicsLinearVelocity(VelStrength * VelNormal);
	//Adding 
	FVector ImpulseAddition = GetActorForwardVector() * MoveSpeed * DeltaTime;
	HeadMesh->AddImpulse(ImpulseAddition, FName(), true);
}

// Called to bind functionality to input
void AWorm::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

