// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputComponent;



UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APlayerController* GetTankPlayerController() const;

	bool IsAlive = true;

	
	
private:
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, Category = "Custom|Components")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category = "Custom|Components")
	UCameraComponent* Camera;
	
#pragma endregion

#pragma region Motion Functions
	
	void Move (float Value);

	void Turn (float Value);


#pragma endregion

#pragma region Motion Values

	UPROPERTY(EditAnywhere, Category = "Custom|Motion");
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Custom|Motion")
	float TurnSpeed;
	
#pragma endregion

	APlayerController* PlayerControllerPtr;

};
