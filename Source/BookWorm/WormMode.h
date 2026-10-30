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

	AWormMode();

private:
	int Score = 0;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ScoreWidgetClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ObjectiveWidgetClass;
	UPROPERTY()
	TArray<FName> CurrentActiveObjectives = {};
	UPROPERTY()
	float ScoreMultiplier = 1.f;
public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void AlterScore(int ScoreChange);
	UFUNCTION()
	void SetScore(int NewScore);
	UFUNCTION()
	int GetScore();
	UFUNCTION()
	void ObjectiveStarted(FName ObjectiveName);
	UFUNCTION()
	void ObjectiveEnded(FName ObjectiveName);
	UFUNCTION(BlueprintCallable)
	void ObjectiveStatusChanged(FName ObjectiveName, FString NewStatus);
	UFUNCTION()
	bool HasObjective(FName ObjectiveName);
	UFUNCTION(BlueprintCallable)
	float GetComboMultiplier();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged,int,NewScore);
	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveAdded, FName, NewObjective);
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveAdded OnObjectiveAdded;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveRemoved, int, ObjectiveIndex);
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveRemoved OnObjectiveRemoved;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectiveUpdated, int, ObjectiveIndex, FString, NewStatus);
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnObjectiveUpdated;
};
