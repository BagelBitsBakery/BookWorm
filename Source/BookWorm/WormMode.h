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
	//The current score of the player/game/level
	UPROPERTY()
	int Score = 0;
protected:
	virtual void BeginPlay() override;

	//Widget class for showing the score
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ScoreWidgetClass;
	//Widget class for showing the objectives
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ObjectiveWidgetClass;
	//All currently active objectives
	UPROPERTY()
	TArray<FName> CurrentActiveObjectives = {};
	//Current multipler used when altering the scores
	UPROPERTY()
	float ScoreMultiplier = 1.f;
public:
	virtual void Tick(float DeltaTime) override;
	//Adds ScoreChange to the current score, also increases multiplier
	UFUNCTION()
	void AlterScore(int ScoreChange);
	//Sets the current score property
	UFUNCTION()
	void SetScore(int NewScore);
	//returns current score
	UFUNCTION()
	int GetScore();
	//Starts tracking of the objective
	UFUNCTION()
	void ObjectiveStarted(FName ObjectiveName);
	//Ends tracking of the objective
	UFUNCTION()
	void ObjectiveEnded(FName ObjectiveName);
	//Updates the status of an active objective
	UFUNCTION(BlueprintCallable)
	void ObjectiveStatusChanged(FName ObjectiveName, FString NewStatus);
	//retuns if an objective is in the current objectives
	UFUNCTION()
	bool HasObjective(FName ObjectiveName);
	//returns combo multiplier
	UFUNCTION(BlueprintCallable)
	float GetComboMultiplier();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged,int,NewScore);
	//Broadcast when score is changed
	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveAdded, FName, NewObjective);
	//Broadcast when an objective is started
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveAdded OnObjectiveAdded;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveRemoved, int, ObjectiveIndex);
	//Broadcast when an objective is ended
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveRemoved OnObjectiveRemoved;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectiveUpdated, int, ObjectiveIndex, FString, NewStatus);
	//Broadcast when an objective is updated
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnObjectiveUpdated;
};
