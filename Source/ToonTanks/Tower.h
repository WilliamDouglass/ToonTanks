// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"


class ATank;

UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Custom|Combat")
	float TowerRange;

	UPROPERTY(EditAnywhere,Category = "Custom|Combat")
	float FireRate;
	FTimerHandle FireRateTimmerHandle;
	void CheckFireCondition();

	bool TankInRange();
	
	ATank* Tank;
	
};
