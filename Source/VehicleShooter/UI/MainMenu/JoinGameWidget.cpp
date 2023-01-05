// Fill out your copyright notice in the Description page of Project Settings.


#include "JoinGameWidget.h"
#include "VehicleShooter/UI/MainMenu/GameModeSelectButton.h"

bool UJoinGameWidget::Initialize() 
{
    Super::Initialize();

    if(DominationGameModeButton)
    {
        DominationGameModeButton->GameModeSelectedDelegate.AddDynamic(this, &UJoinGameWidget::GameModeSelected);
    }
    if(ControlGameModeButton)
    {
        ControlGameModeButton->GameModeSelectedDelegate.AddDynamic(this, &UJoinGameWidget::GameModeSelected);
    }
    if(TDMGameModeButton)
    {
        TDMGameModeButton->GameModeSelectedDelegate.AddDynamic(this, &UJoinGameWidget::GameModeSelected);
    }
    return true;
}

void UJoinGameWidget::GameModeSelected(EGameModes GameModeEnum) 
{
    GameModeChosenDelegate.Broadcast(GameModeEnum);
}
