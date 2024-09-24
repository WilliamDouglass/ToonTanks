// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

	GetWorldTimerManager().SetTimer(FireRateTimmerHandle,this,&ATower::CheckFireCondition,FireRate,true);
	
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(TankInRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	UE_LOG(LogTemp, Display, TEXT("Tower Dead"));
	Super::HandleDestruction();
	Destroy();
}


bool ATower::TankInRange()
{
	if(Tank)
	{
		float TargetDistance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if(TargetDistance <= TowerRange)
		{
			return true;
		}
	}
	return false;
}


void ATower::CheckFireCondition()
{
	if(TankInRange() && Tank->IsAlive)
	{
		Fire();
	}
}
