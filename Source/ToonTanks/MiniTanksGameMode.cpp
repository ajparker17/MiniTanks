// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniTanksGameMode.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.h"

void AMiniTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AMiniTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (Tank->GetPlayerControllerRef())
		{
			Tank->DisableInput(Tank->GetPlayerControllerRef());
			Tank->GetPlayerControllerRef()->bShowMouseCursor = false;
		}	
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
	}
}

