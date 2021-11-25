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
		GameOver(false);
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		--TurretCount;
		if (TurretCount == 0)
		{
			GameOver(true);
		}
	}
}

void AMiniTanksGameMode::HandleGameStart()
{

	TurretCount = GetTurretCount();

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

int32 AMiniTanksGameMode::GetTurretCount()
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(),Turrets);
	return Turrets.Num();
}

