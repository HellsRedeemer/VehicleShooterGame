// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleShooterGameState.h"
#include "VehicleShooter/PlayerController/VehicleShooterController.h"
#include "Net/UnrealNetwork.h"

void AVehicleShooterGameState::TeamScored(ETeams TeamWhichScored, uint32 NewScore) 
{
    
    UE_LOG(LogTemp, Warning, TEXT("GOT HERE"));
    if(Teams.Contains(TeamWhichScored))
    {
        TeamsScores[Teams.Find(TeamWhichScored)] = NewScore;
    }
    else
    {
        Teams.Add(TeamWhichScored);
        TeamsScores.Add(NewScore);
    }

    AVehicleShooterController* Controller = Cast<AVehicleShooterController>(GetWorld()->GetFirstPlayerController());
    if(Controller)
    {
        Controller->UpdateHUDScores(Teams, TeamsScores);
    }
}


void AVehicleShooterGameState::OnRep_TeamsScores() 
{
    AVehicleShooterController* Controller = Cast<AVehicleShooterController>(GetWorld()->GetFirstPlayerController());
    if(Controller)
    {
        Controller->UpdateHUDScores(Teams, TeamsScores);
    }
}

void AVehicleShooterGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AVehicleShooterGameState, Teams);
    DOREPLIFETIME(AVehicleShooterGameState, TeamsScores);
}
