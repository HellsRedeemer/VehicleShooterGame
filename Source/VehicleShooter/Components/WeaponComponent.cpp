// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "VehicleShooter/Projectile/BaseProjectile.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::FireWeapon() 
{
	Server_FireWeapon();
	//
}

void UWeaponComponent::Server_FireWeapon_Implementation() 
{
	if(FiringPoint && ProjectileClass.IsValid())
	{
		GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass.Get(), FiringPoint->GetComponentLocation(), FiringPoint->GetComponentRotation());
	}
}

void UWeaponComponent::StopFiringWeapon() 
{
	
}





