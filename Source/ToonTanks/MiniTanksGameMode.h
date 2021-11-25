// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AMiniTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

private:
	class ATank* Tank;
	class AMiniTanksPlayerController* MiniTankPlayerController;

	float StartDelay = 3.0f;
	void HandleGameStart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	
};
