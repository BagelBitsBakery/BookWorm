// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "EatingObjective.generated.h"

class AEdibleObject;
/**
 * 
 */
UCLASS()
class BOOKWORM_API AEatingObjective : public AObjective
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	int EatingNeeded = 0;
	UPROPERTY()
	int EatenAmount = 0;

	UFUNCTION()
	void Eaten();
protected:
	virtual void BeginPlay() override;
public:
	//Array of edible objects meant to be set in editor. Objective ends when all objects in this array are eaten
	UPROPERTY(EditAnywhere)
	TArray<AEdibleObject*> OnesThatNeedEating;

};
