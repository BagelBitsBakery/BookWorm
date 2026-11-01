// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrackComponent.h"

// Sets default values for this component's properties
UTimeTrackComponent::UTimeTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	RegisterComponent();
}


// Called when the game starts
void UTimeTrackComponent::BeginPlay()
{
	Super::BeginPlay();
	RegisterComponent();
	SetComponentTickEnabled(false);
	
}


// Called every frame
void UTimeTrackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeElapsed += DeltaTime;
	TimerDisplay->UpdateTimer(TimeElapsed);
}

void UTimeTrackComponent::StartRaceTimer()
{
	if (!IsValid(TimerDisplay)) {
		TimerDisplay = CreateWidget<UTimerWidget>(GetOwner()->GetWorld(), TimerWidgetClass);
		UE_LOG(LogTemp, Display, TEXT("Time Track Component: Timer Widget Create"));
	};
	TimerDisplay->AddToViewport();
	TimerDisplay->UpdateTimer(0.f);
	SetComponentTickEnabled(true);
	TimeElapsed = 0.f;
	UE_LOG(LogTemp, Display, TEXT("Time Track Component: Timer Started"));
}

void UTimeTrackComponent::EndRaceTimer()
{
	SetComponentTickEnabled(false);
	TimerDisplay->RemoveFromViewport();
}

float UTimeTrackComponent::GetRaceTime()
{
	return TimeElapsed;
}

