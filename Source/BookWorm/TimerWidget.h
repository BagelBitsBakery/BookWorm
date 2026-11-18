// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOOKWORM_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// A function designed to be overriden by a blueprint widget class
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimer(float NewTime);
	
};
