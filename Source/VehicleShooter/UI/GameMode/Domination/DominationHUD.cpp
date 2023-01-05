// Fill out your copyright notice in the Description page of Project Settings.


#include "DominationHUD.h"
#include "GameFramework/PlayerController.h"
#include "DominationWidget.h"


void ADominationHUD::BeginPlay() 
{
    Super::BeginPlay();
    APlayerController* PlayerController = GetOwningPlayerController();
    if(PlayerController && DominationWidgetClass)
    {   
        DominationWidget = CreateWidget<UDominationWidget>(PlayerController, DominationWidgetClass);
        if(DominationWidget)
        {
            DominationWidget->AddToViewport();
        }
    }

}

void ADominationHUD::UpdateTeamScore(const TArray<ETeams> Teams, const TArray<uint32> Scores) 
{
    Super::UpdateTeamScore(Teams, Scores);
    if(DominationWidget)
    {
        DominationWidget->UpdateTeamScores(Teams, Scores);
    }
}
