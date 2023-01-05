// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameModeHUD.h"
#include "VehicleShooter/UI/Vehicle/MainHUD.h"
#include "VehicleShooter/UI/Misc/PauseWidget.h"

void ABaseGameModeHUD::BeginPlay() 
{
    Super::BeginPlay();
    if(MainUIClass)
    {
        MainHUD = CreateWidget<UMainHUD>(GetOwningPlayerController(), MainUIClass);
        if(MainHUD)
        {
            MainHUD->AddToViewport();
            FinishedSetup.Broadcast();
        }
    }
    if(PauseWidgetClass)
    {
        PauseWidget = CreateWidget<UPauseWidget>(GetOwningPlayerController(), PauseWidgetClass);
       /* if(PauseWidget)
        {
            PauseWidget->AddToViewport();
        }*/
    }
}

void ABaseGameModeHUD::UpdateTeamScore(const TArray<ETeams> Teams, const TArray<uint32> Scores) 
{
    //UE_LOG(LogTemp, Warning, TEXT("base scores UPDATED"));
}

void ABaseGameModeHUD::TogglePauseMenu() 
{
   // UE_LOG(LogTemp, Warning, TEXT(" TOGGLE"));
    if(PauseWidget)
    { 
        if(PauseWidget->IsInViewport())
        {
            PauseWidget->RemoveFromViewport();
            if(GetOwningPlayerController())
            {
                FInputModeGameOnly InputMode;
                GetOwningPlayerController()->SetInputMode(InputMode);
                GetOwningPlayerController()->bShowMouseCursor = false;
            }
        }
        else
        {
            PauseWidget->AddToViewport();
            if(GetOwningPlayerController())
            {
                FInputModeGameAndUI InputMode;
                //InputMode.SetHideCursorDuringCapture(false);
                GetOwningPlayerController()->SetInputMode(InputMode);
                GetOwningPlayerController()->bShowMouseCursor = true;
            }
        }
    }
}
