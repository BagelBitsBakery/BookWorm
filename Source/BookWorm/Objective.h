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

	UFUNCTION(BlueprintCallable)
	void StartObjective();
	UFUNCTION(BlueprintCallable)
	void EndObjective();
	UFUNCTION(BlueprintCallable)
	void UpdateObStatus(FString Status);

	UPROPERTY(EditDefaultsOnly)
	UWormDetectorComponent* Detector;
	UPROPERTY(EditDefaultsOnly)
	UScoreGiveComponent* ScoreGive;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* EnterDetection;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ObjectiveName;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectiveStarted);
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveStarted OnObjectiveStarted;
	
	UPROPERTY();
	bool IsActive = false;
	UPROPERTY();
	bool IsComplete = false;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectiveEnded);
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveEnded OnObjectiveEnded;

};
