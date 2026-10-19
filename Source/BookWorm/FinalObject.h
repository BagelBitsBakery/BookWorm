// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdibleObject.h"
#include "FinalObject.generated.h"

/**
 * 
 */
UCLASS()
class BOOKWORM_API AFinalObject : public AEdibleObject
{
	GENERATED_BODY()

protected:
	virtual void EatEffect() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WidgetClass;
};
