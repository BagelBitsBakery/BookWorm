// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "CowPenObjective.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class BOOKWORM_API ACowPenObjective : public AObjective
{
	GENERATED_BODY()

	ACowPenObjective();
public:
	UPROPERTY(EditDefaultsOnly)
	int CowsNeeded = 3;
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void CowEntered();

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	
private:
	UPROPERTY()
	int CowsEntered = 0;
	UPROPERTY()
	TArray<AActor*> ActorsInPen = {};
};
