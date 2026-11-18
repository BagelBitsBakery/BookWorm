// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objective.generated.h"

class UWormDetectorComponent;
class UScoreGiveComponent;
class USphereComponent;

UCLASS()
class BOOKWORM_API AObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Starts the objective
	UFUNCTION(BlueprintCallable)
	void StartObjective();
	//Ends the objective, giving score in the process
	UFUNCTION(BlueprintCallable)
	void EndObjective();
	//Broadcasts a signal to the game mode, making objective update on the UI
	UFUNCTION(BlueprintCallable)
	void UpdateObStatus(FString Status);

	//Child Components
	UPROPERTY(EditDefaultsOnly)
	UWormDetectorComponent* Detector;
	UPROPERTY(EditDefaultsOnly)
	UScoreGiveComponent* ScoreGive;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* EnterDetection;

	//Objective Info
	//The name, used for identifying it and display on UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ObjectiveName;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectiveStarted);
	//Broadcast when the objective Starts
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveStarted OnObjectiveStarted;
	
	//The active state of the objective
	UPROPERTY();
	bool IsActive = false;
	//The complete state of the objective
	UPROPERTY();
	bool IsComplete = false;
	
public:	

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectiveEnded);
	//Broadcast when objective ended
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveEnded OnObjectiveEnded;

};
