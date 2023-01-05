// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlGameModeHUD.h"
#include "ControlWidget.h"

void AControlGameModeHUD::BeginPlay() 
{
    Super::BeginPlay();
    APlayerController* PlayerController = GetOwningPlayerController();
    if(PlayerController && ControlWidgetClass)
    {   
        ControlWidget = CreateWidget<UControlWidget>(PlayerController, ControlWidgetClass);
        if(ControlWidget)
        {
            ControlWidget->AddToViewport();
        }
    }

}