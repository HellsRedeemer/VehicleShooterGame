// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleShooterPlayerState.h"
#include "VehicleShooter/Vehicles/BaseVehicle.h"
#include "Net/UnrealNetwork.h"

void AVehicleShooterPlayerState::SetTeam(ETeams WhichTeam) 
{
    Team = WhichTeam;
}

void AVehicleShooterPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AVehicleShooterPlayerState, Team);
}

void AVehicleShooterPlayerState::OnRep_Team() 
{
    ABaseVehicle* Player = Cast<ABaseVehicle>(GetPawn());
    if(Player)
    {
        Player->SetTeam(Team);
    }
}
