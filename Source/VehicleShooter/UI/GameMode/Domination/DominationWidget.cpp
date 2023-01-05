// Fill out your copyright notice in the Description page of Project Settings.


#include "DominationWidget.h"
#include "Components/TextBlock.h"

void UDominationWidget::UpdateTeamScores(const TArray<ETeams> Teams, const TArray<uint32> Scores) 
{
    UE_LOG(LogTemp, Warning, TEXT("SCORE UPDATED"));
    if(Teams.Contains(ETeams::ET_RedTeam) && RedTeamScore)
    {
        FString ScoreText = FString::Printf(TEXT("%i"), Scores[Teams.Find(ETeams::ET_RedTeam)]);
        RedTeamScore->SetText(FText::FromString(ScoreText));
    }
    if(Teams.Contains(ETeams::ET_BlueTeam) && BlueTeamScore)
    {
        FString ScoreText = FString::Printf(TEXT("%i"), Scores[Teams.Find(ETeams::ET_BlueTeam)]);
        BlueTeamScore->SetText(FText::FromString(ScoreText));
    }
}
