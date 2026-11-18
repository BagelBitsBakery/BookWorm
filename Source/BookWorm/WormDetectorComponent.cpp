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

	//Checks if the shape or component ref for shape are valid
	if (!IsValid(ShapeForDetection))
		//Turns the component ref into a shape component
		ShapeForDetection = Cast<UShapeComponent>(ComponentRef.GetComponent(GetOwner()));
	if (IsValid(ShapeForDetection)) {
		ShapeForDetection->OnComponentBeginOverlap.AddDynamic(this, &UWormDetectorComponent::OverlapBegin);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Worm Detect Has No Shape %s"),*GetOwner()->GetName());
	}
	
}

void UWormDetectorComponent::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AWorm* Worm = Cast<AWorm>(OtherActor)) {
		OnWormDetected.Broadcast();
		OnWormEntered.Broadcast(Worm);
	}
}
