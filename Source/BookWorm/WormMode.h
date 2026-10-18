// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WormMode.generated.h"

/**
 * 
 */
UCLASS()
class BOOKWORM_API AWormMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	int Score = 0;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WidgetClass;
public:
	void AlterScore(int ScoreChange);
	void SetScore(int NewScore);
	int GetScore();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreChanged);
	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;
};
