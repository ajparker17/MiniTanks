// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniTanksGameMode.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.h"
#include "MiniTanksPlayerController.h"

void AMiniTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AMiniTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (MiniTankPlayerController)
		{
			MiniTankPlayerController->SetPlayerEnableState(false);
		}	
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
	}
}

void AMiniTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	MiniTankPlayerController = Cast<AMiniTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (MiniTankPlayerController)
	{
		MiniTankPlayerController->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			MiniTankPlayerController,
			&AMiniTanksPlayerController::SetPlayerEnableState,
			true
		);

		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
		);
	}
}

