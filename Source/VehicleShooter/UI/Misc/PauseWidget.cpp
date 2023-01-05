// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"


bool UPauseWidget::Initialize() 
{
    Super::Initialize();

    if(QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UPauseWidget::QuitGame);
    }
    
    if(MainMenuButton)
    {
        MainMenuButton->OnClicked.AddDynamic(this, &UPauseWidget::MainMenu);
    }
    return true;
}

void UPauseWidget::QuitGame() 
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}

void UPauseWidget::MainMenu() 
{
    if(GetOwningPlayer())
    {
        GetOwningPlayer()->ClientReturnToMainMenuWithTextReason(FText());
    }
}
