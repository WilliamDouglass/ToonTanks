// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"),this,&ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this, &ATank::Fire);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerControllerPtr = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PlayerControllerPtr)
	{
		FHitResult HitResult;
		PlayerControllerPtr->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
		RotateTurret(HitResult.ImpactPoint);

	}
	
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	IsAlive = false;
}


void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::Zero();
	DeltaLocation.X = Value * MoveSpeed * GetWorld()->DeltaTimeSeconds;
	AddActorLocalOffset(DeltaLocation);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRoatation = FRotator::ZeroRotator;
	DeltaRoatation.Yaw = Value * TurnSpeed * GetWorld()->DeltaTimeSeconds;
	AddActorLocalRotation(DeltaRoatation,true);
}

APlayerController* ATank::GetTankPlayerController() const
{
	return PlayerControllerPtr;
}


