// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"

#include "Tank.h"
#include "ToonTankPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTankPlayerController)
		{
			ToonTankPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		NumTowers--;
		if(NumTowers == 0 )
		{
			GameOver(true);
		}
	}
}


void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();

	
	
}

void AToonTankGameMode::HandleGameStart()
{
	NumTowers = GetTotalNumTowers();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this,0));

	StartGame();

	if (ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerStartTimmerHandle;
		
		FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(
			ToonTankPlayerController,
			&AToonTankPlayerController::SetPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(PlayerStartTimmerHandle,InputDelegate,StartDelay,false);
		
	}
	
}


int AToonTankGameMode::GetTotalNumTowers()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),Towers);
	return Towers.Num();
}
