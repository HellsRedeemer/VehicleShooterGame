// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleShooterController.h"
#include "VehicleShooter/UI/GameMode/BaseGameModeHUD.h"

void AVehicleShooterController::UpdateHUDScores(const TArray<ETeams> Teams, const TArray<uint32> TeamScores) 
{
    GameHUD = GameHUD == nullptr ? Cast<ABaseGameModeHUD>(GetHUD()) : GameHUD;
    if(GameHUD)
    {
        GameHUD->UpdateTeamScore(Teams, TeamScores);
    }
}
