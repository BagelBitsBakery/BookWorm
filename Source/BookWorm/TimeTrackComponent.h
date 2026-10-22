// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerWidget.h"
#include "TimeTrackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOOKWORM_API UTimeTrackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeTrackComponent();

private:
	UPROPERTY()
	float TimeElapsed = 0.f;
	UPROPERTY()
	UTimerWidget* TimerDisplay;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void StartRaceTimer();
	UFUNCTION()
	void EndRaceTimer();
	UFUNCTION()
	float GetRaceTime();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTimerWidget> TimerWidgetClass;
		
};
