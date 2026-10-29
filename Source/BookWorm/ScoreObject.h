// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdibleObject.h"
#include "ScoreObject.generated.h"

class UScoreGiveComponent;
class AWorm;

/**
 * 
 */
UCLASS()
class BOOKWORM_API AScoreObject : public AEdibleObject
{
	GENERATED_BODY()

	AScoreObject();

protected:
	virtual void EatEffect() override;
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UScoreGiveComponent* ScoreGive;
	UFUNCTION()
	void WormGrow(AWorm* Worm);
	
};
