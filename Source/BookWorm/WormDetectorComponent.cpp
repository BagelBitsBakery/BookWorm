// Fill out your copyright notice in the Description page of Project Settings.


#include "WormDetectorComponent.h"
#include "Worm.h"

// Sets default values for this component's properties
UWormDetectorComponent::UWormDetectorComponent()
{
	
}


// Called when the game starts
void UWormDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(ShapeForDetection)) {
		ShapeForDetection->OnComponentBeginOverlap.AddDynamic(this, &UWormDetectorComponent::OverlapBegin);
		ShapeForDetection->AttachToComponent(GetOwner()->GetRootComponent(),FAttachmentTransformRules(EAttachmentRule::KeepRelative,true));
	}
	
}

void UWormDetectorComponent::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AWorm>(OtherActor)) {
		OnWormDetected.Broadcast();
	}
}
