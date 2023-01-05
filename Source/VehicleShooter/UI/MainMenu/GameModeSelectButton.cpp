// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeSelectButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


bool UGameModeSelectButton::Initialize() 
{
    Super::Initialize();

    if(GameModeButton)
    {
        GameModeButton->OnClicked.AddDynamic(this, &UGameModeSelectButton::GameModeButtonPressed);
    }
    if(GameModeTextBlock)
    {
        //find better way to get display name

        GameModeTextBlock->SetText(ButtonText);
    }

    return true;
}


void UGameModeSelectButton::GameModeButtonPressed() 
{
    //UE_LOG(LogTemp, Warning, TEXT("BUTTON PRESSED"));
    GameModeSelectedDelegate.Broadcast(WhichGameMode);
}




