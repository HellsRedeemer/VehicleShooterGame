// Fill out your copyright notice in the Description page of Project Settings.


#include "DominationGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "VehicleShooter/GameState/VehicleShooterGameState.h"
#include "DominationFlag.h"


void ADominationGameMode::BeginPlay() 
{   
    TArray<AActor*> FoundFlags;
    UGameplayStatics::GetAllActorsOfClass(this, ADominationFlag::StaticClass(), FoundFlags);

    for(AActor* Flag : FoundFlags)
    {
        DominationFlags.Add(Cast<ADominationFlag>(Flag));
    }
    for(ADominationFlag* Flag : DominationFlags)
    {
        Flag->FlagCaptureDelegate.AddDynamic(this, &ADominationGameMode::DominationFlagCaptured);
    }
    UE_LOG(LogTemp, Warning, TEXT("Domination flags found: %i"), DominationFlags.Num());

    GetWorldTimerManager().SetTimer(AddCaptureScoreHandle, this, &ADominationGameMode::AddScore, TimeBetweenPointGained, true);
}

void ADominationGameMode::DominationFlagCaptured(ETeams TeamThatCaptured, ETeams TeamThatLostFlag) 
{
    DominationFlagLost(TeamThatLostFlag);
    if(TeamsAndFlagCount.Contains(TeamThatCaptured))
    {   
        TeamsAndFlagCount.Add(TeamThatCaptured) = TeamsAndFlagCount[TeamThatCaptured] + 1;
    }
    else
    {
        TeamsAndFlagCount.Add(TeamThatCaptured , 1);
    }
    UE_LOG(LogTemp, Warning, TEXT("GAMEMODE DETECTS A FLAG WAS CAPTURED team now holds: %i"), TeamsAndFlagCount[TeamThatCaptured]);
}

void ADominationGameMode::DominationFlagLost(ETeams TeamThatLostFlag) 
{
    if(TeamsAndFlagCount.Contains(TeamThatLostFlag))
    {
        TeamsAndFlagCount.Add(TeamThatLostFlag) = FMath::Clamp(TeamsAndFlagCount[TeamThatLostFlag] - 1, 0, 999);
    }
}

void ADominationGameMode::AddScore() 
{
    for(auto FlagHeld : TeamsAndFlagCount)
    {
        if(TeamsAndScore.Contains(FlagHeld.Key))
        {
            TeamsAndScore.Add(FlagHeld.Key) = TeamsAndScore[FlagHeld.Key] + FlagHeld.Value;
        }
        else
        {
            TeamsAndScore.Add(FlagHeld.Key, FlagHeld.Value);
        }
    }

    AVehicleShooterGameState* MyGameState = Cast<AVehicleShooterGameState>(UGameplayStatics::GetGameState(this));

    if(TeamsAndScore.Contains(ETeams::ET_RedTeam) && MyGameState)
    {
        UE_LOG(LogTemp, Warning, TEXT("Red team score is: %i"), TeamsAndScore[ETeams::ET_RedTeam]);
        MyGameState->TeamScored(ETeams::ET_RedTeam, TeamsAndScore[ETeams::ET_RedTeam]);
    }
    if(TeamsAndScore.Contains(ETeams::ET_BlueTeam) && MyGameState)
    {
        UE_LOG(LogTemp, Warning, TEXT("Blue team score is: %i"), TeamsAndScore[ETeams::ET_BlueTeam]);
        MyGameState->TeamScored(ETeams::ET_BlueTeam, TeamsAndScore[ETeams::ET_BlueTeam]);
    }
}   
