// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameStates.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class VRBUS_API AGameManager : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AGameManager();

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	EGameState CurrentState;

	UPROPERTY(BlueprintReadOnly)
	int32 Days = 1;

	UFUNCTION(BlueprintCallable)
	void CurrentStateEvent();

	UFUNCTION(BlueprintCallable)
	void NextState();

protected:

	virtual void BeginPlay() override;

	void StartState();
	void PreparationState();
	void DriveState();
	void BusStopState();
	void SleepState();

};
