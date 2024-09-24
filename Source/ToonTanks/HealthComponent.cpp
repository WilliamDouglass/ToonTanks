// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	ToonTankGameMode = Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(this));

	Health = MaxHealthVal;

	// ...
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Display, TEXT("Actor Damaged"));
	if (Health <= 0)
	{
		return;
	}
	Health -= Damage;
	UE_LOG(LogTemp, Display, TEXT("%s Health %f"), *DamagedActor->GetActorNameOrLabel(), Health);

	if (Health <= 0 && ToonTankGameMode)
	{
		UE_LOG(LogTemp, Display, TEXT("ActorDied %s"), *DamagedActor->GetActorNameOrLabel());
		ToonTankGameMode->ActorDied(DamagedActor);
	}
}














