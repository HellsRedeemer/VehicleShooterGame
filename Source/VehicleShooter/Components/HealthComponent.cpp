// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "VehicleShooter/Gamemode/VehicleShooterGamemode.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//SetIsReplicated(true);
	Health = MaxHealth;
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHealthComponent::DoDamage(float Damage, AActor* DamageCauser, AController* ControllerThatOwnsDamage) 
{
	Health = FMath::Clamp(Health - Damage, 0, MaxHealth);
	WasDamagedDelegate.Broadcast(Damage, Health);
	UE_LOG(LogTemp, Warning, TEXT("NEW HEALTH IS: %f"), Health);

	if(Health <=0 && bShouldRespawn)
	{
		AVehicleShooterGamemode* GameMode = GetWorld()->GetAuthGameMode<AVehicleShooterGamemode>();
		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if(GameMode && OwnerPawn)
		{
			AController* OwnerController = Cast<AController>(OwnerPawn->GetController());
			GameMode->RequestRespawn(OwnerPawn, OwnerController);
		}

	}
}





