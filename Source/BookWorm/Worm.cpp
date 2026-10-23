// Fill out your copyright notice in the Description page of Project Settings.


#include "Worm.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "CameraFollowComponent.h"

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

	Cam = CreateDefaultSubobject<UCameraFollowComponent>(TEXT("Camera"));

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
}

// Called when the game starts or when spawned
void AWorm::BeginPlay()
{
	Super::BeginPlay();
	//redoing this bit here to see if it works now
	HeadMesh->SetSimulatePhysics(true);
	HeadMesh->SetEnableGravity(true);

	HeadMesh->OnComponentBeginOverlap.AddDynamic(this, &AWorm::OverlapBegin);
	HeadMesh->OnComponentEndOverlap.AddDynamic(this, &AWorm::OverlapEnd);
}

// Called every frame
void AWorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Drag
	float TempUnderground = UndergroundValue;
	if (IsUnderSurface()) TempUnderground = 1.f;
	float VelStrength = FVector::Distance(HeadMesh->GetPhysicsLinearVelocity(), FVector::Zero());
	FVector VelNormal = HeadMesh->GetPhysicsLinearVelocity().GetSafeNormal();
	float DragStrength = (VelStrength / MoveSpeed) * AirDrag;
	VelStrength -= DragStrength * DeltaTime * TempUnderground;
	HeadMesh->SetPhysicsLinearVelocity(VelStrength * VelNormal);
	//Adding 
	FVector ImpulseAddition = GetActorForwardVector() * MoveSpeed * DeltaTime;
	HeadMesh->AddImpulse(ImpulseAddition * TempUnderground, FName(), true);
}

// Called to bind functionality to input
void AWorm::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(MoveInputMap, 0);
		}

	}
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWorm::MovementInputPressed);
	}

}

void AWorm::MovementInputPressed(const FInputActionValue& Value)
{
	FVector2D MovementVal = Value.Get<FVector2D>() * FMath::Lerp(0.35,1.f,UndergroundValue);
	AddControllerPitchInput(MovementVal.Y);
	AddControllerYawInput(MovementVal.X);
}

void AWorm::GoUnderground()
{
	UndergroundValue = 1.f;
	HeadMesh->SetEnableGravity(false);
}

void AWorm::GoAboveGround()
{
	UndergroundValue = 0.f;
	HeadMesh->SetEnableGravity(true);
}

void AWorm::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("DigGround")) {
		if (ActorsInDig.Contains(OtherActor)) return;
		GroundsCollided += 1;
		ActorsInDig.Add(OtherActor);
		if (GroundsCollided > 0 and UndergroundValue < 1.f) {
			GoUnderground();
		}
	}
}

void AWorm::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("DigGround")) {
		GroundsCollided -= 1;
		ActorsInDig.Remove(OtherActor);
		if (GroundsCollided < 1 and UndergroundValue > 0.f) {
			GoAboveGround();
		}
	}
}

bool AWorm::IsUnderSurface()
{
	FHitResult OutHit = FHitResult();
	FVector ActorPos = GetActorLocation();
	FVector Start = FVector(0.f, 0.f, 75000);
	FVector End = ActorPos;
	FCollisionQueryParams Params;
	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	if (OutHit.bBlockingHit) {
		HeadMesh->SetEnableGravity(false);
		return true;
	}
	if (UndergroundValue != 1.f) HeadMesh->SetEnableGravity(true);
	return false;
}
