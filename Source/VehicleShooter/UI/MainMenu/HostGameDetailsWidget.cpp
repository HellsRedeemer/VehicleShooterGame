// Fill out your copyright notice in the Description page of Project Settings.


#include "HostGameDetailsWidget.h"
#include "VehicleShooter/UI/MainMenu/GameModeSelectButton.h"

bool UHostGameDetailsWidget::Initialize() 
{
    Super::Initialize();

    if(DominationGameModeButton)
    {
        DominationGameModeButton->GameModeSelectedDelegate.AddDynamic(this, &UHostGameDetailsWidget::GameModeSelected);
    }
    if(ControlGameModeButton)
    {
        ControlGameModeButton->GameModeSelectedDelegate.AddDynamic(this, &UHostGameDetailsWidget::GameModeSelected);
    }
    if(TDMGameModeButton)
    {
        TDMGameModeButton->GameModeSelectedDelegate.AddDynamic(this, &UHostGameDetailsWidget::GameModeSelected);
    }
    return true;
}

void UHostGameDetailsWidget::GameModeSelected(EGameModes GameModeEnum) 
{
    GameModeSelectedDelegate.Broadcast(GameModeEnum);
}
