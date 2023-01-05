// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAi.h"

#include "VehicleShooter/Components/HealthComponent.h"

// Sets default values
ABaseAi::ABaseAi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComp = CreateDefaultSubobject<UHealthComponent>("Health Comp");
}

// Called when the game starts or when spawned
void ABaseAi::BeginPlay()
{
	Super::BeginPlay();
	
}

