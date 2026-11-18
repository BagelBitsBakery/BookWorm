// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "CowPenObjective.generated.h"

class UBoxComponent;

/**
 A class for detecting cows in a pen and making it an objective.
 */
UCLASS()
class BOOKWORM_API ACowPenObjective : public AObjective
{
	GENERATED_BODY()

	ACowPenObjective();
public:
	//Hows many cows are needed to enter the pen to complete the objective
	UPROPERTY(EditDefaultsOnly)
	int CowsNeeded = 3;
protected:
	virtual void BeginPlay() override;
	//Called when something overlaps the box collision
	UFUNCTION()
	void BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//Called by box overlap if the other actos is a cow
	UFUNCTION()
	void CowEntered();

	//A box for detecting physics components
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	
private:
	//The current number of cows that have been detected
	UPROPERTY()
	int CowsEntered = 0;
	//Tracking the cows that entered so the same actor can't be detected twice
	UPROPERTY()
	TArray<AActor*> ActorsInPen = {};
};
