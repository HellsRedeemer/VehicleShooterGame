// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "HostGameDetailsWidget.h"
#include "JoinGameWidget.h"
#include "Kismet/KismetSystemLibrary.h"

bool UMainMenuWidget::Initialize() 
{
    if(!Super::Initialize())
    {
        return false;    
    }

    if(HostButton)
    {
        HostButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HostButtonClicked);
    }
    if(JoinButton)
    {
        JoinButton->OnClicked.AddDynamic(this, &UMainMenuWidget::JoinButtonClicked);
    }
    if(HostDetailsWidget)
    {
        HostDetailsWidget->GameModeSelectedDelegate.AddDynamic(this, &UMainMenuWidget::GameModeSelected);
    }
    if(JoinGameWidget)
    {
        JoinGameWidget->GameModeChosenDelegate.AddDynamic(this, &UMainMenuWidget::GameModeToJoinSelected);
    }
    if(BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &UMainMenuWidget::BackToMainMenu);
    }
    if(QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
    }

    GameModeAndPaths.Emplace(EGameModes::EGM_NoMode, FString(""));
    GameModeAndPaths.Emplace(EGameModes::EGM_Domination, FString("/Game/Blueprints/Gamemode/Domination/BP_GM-Domination.BP_GM-Domination_C"));
    GameModeAndPaths.Emplace(EGameModes::EGM_Control, FString("/Game/Blueprints/Gamemode/Control/BP_ControlGameMode.BP_ControlGameMode_C"));
    //GameModeAndPaths.Emplace(EGameModes::EGM_Domination, FString("/Game/Blueprints/Gamemode/Domination/BP_GM-Domination.BP_GM-Domination_C"));

	return true;
}

void UMainMenuWidget::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch, FString LobbyPath) 
{
    PathToLobby = FString::Printf(TEXT("%s?listen"), *LobbyPath);
    NumPublicConnections = NumberOfPublicConnections;
    MatchType = TypeOfMatch;

	AddToViewport();
    SetVisibility(ESlateVisibility::Visible);
    bIsFocusable = true;

    UWorld* World = GetWorld();
    if(World)
    {
        APlayerController* PlayerController = World->GetFirstPlayerController();
        if(PlayerController)
        {
            FInputModeUIOnly InputModeData;
            InputModeData.SetWidgetToFocus(TakeWidget());
            InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            PlayerController->SetInputMode(InputModeData);
            PlayerController->SetShowMouseCursor(true);
        }
    }
    UGameInstance* GameInstance = GetGameInstance();
    if(GameInstance)
    {
        MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();
    }

    if(MultiplayerSessionSubsystem)
    {
        MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &UMainMenuWidget::OnCreateSession);
        MultiplayerSessionSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &UMainMenuWidget::OnFindSessions);
        MultiplayerSessionSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &UMainMenuWidget::OnJoinSession);
        MultiplayerSessionSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &UMainMenuWidget::OnDestroySession);
        MultiplayerSessionSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &UMainMenuWidget::OnStartSession);
    }
    

}

void UMainMenuWidget::HostButtonClicked() 
{
    /*
    HostButton->SetIsEnabled(false);
	//UE_LOG(LogTemp, Warning, TEXT("Host button Clicked"));
    if(MultiplayerSessionSubsystem)
    {
        MultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
    }*/
    if(HostDetailsWidget)
    {
        HostDetailsWidget->SetVisibility(ESlateVisibility::Visible);
        BackButton->SetVisibility(ESlateVisibility::Visible);

        HostButton->SetVisibility(ESlateVisibility::Hidden);
        JoinButton->SetVisibility(ESlateVisibility::Hidden);
        QuitButton->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UMainMenuWidget::JoinButtonClicked() 
{
    if(JoinGameWidget)
    {
        JoinGameWidget->SetVisibility(ESlateVisibility::Visible);
        BackButton->SetVisibility(ESlateVisibility::Visible);

        HostButton->SetVisibility(ESlateVisibility::Hidden);
        JoinButton->SetVisibility(ESlateVisibility::Hidden);
        QuitButton->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UMainMenuWidget::GameModeSelected(EGameModes GameMode) 
{
   // find a better way to get display names
  
    MatchType = UEnum::GetDisplayValueAsText(GameMode).ToString();
    SelectedGameMode = GameMode; 

    //MatchType = GameMode.ToString();
    HostButton->SetIsEnabled(false);
	//UE_LOG(LogTemp, Warning, TEXT("Host button Clicked"));
    if(MultiplayerSessionSubsystem)
    {
        MultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
    }
}

void UMainMenuWidget::GameModeToJoinSelected(EGameModes GameMode) 
{   
    UE_LOG(LogTemp, Warning, TEXT("JOIN A GMAE"))
    // find a better way to get display names
    MatchType = UEnum::GetDisplayValueAsText(GameMode).ToString();
    SelectedGameMode = GameMode; 

    JoinButton->SetIsEnabled(false);
    if(MultiplayerSessionSubsystem)
    {
        MultiplayerSessionSubsystem->FindSessions(99999);
        //MultiplayerSessionSubsystem->JoinSession();
    }
}

void UMainMenuWidget::BackToMainMenu() 
{
    JoinGameWidget->SetVisibility(ESlateVisibility::Hidden);
    HostDetailsWidget->SetVisibility(ESlateVisibility::Hidden);
    BackButton->SetVisibility(ESlateVisibility::Hidden);

    HostButton->SetVisibility(ESlateVisibility::Visible);
    JoinButton->SetVisibility(ESlateVisibility::Visible);
    QuitButton->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::QuitGame() 
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}



void UMainMenuWidget::NativeDestruct() 
{
    MenuTearDown();
    Super::NativeDestruct();
}

void UMainMenuWidget::MenuTearDown() 
{
    UWorld* World = GetWorld();
    if(World)
    {
        APlayerController* PlayerController = World->GetFirstPlayerController();
        if(PlayerController)
        {
            FInputModeGameOnly InputModeData;
            PlayerController->SetInputMode(InputModeData);
            PlayerController->SetShowMouseCursor(false);
        }
    }

    RemoveFromParent();
}


void UMainMenuWidget::OnCreateSession(bool bWasSuccessful) 
{
    //UE_LOG(LogTemp, Warning, TEXT("MAKE SESSION"));
	if(bWasSuccessful)
    {
        if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("session Created")));
		}
        
        UWorld* World = GetWorld();
        if(World)
        { 
            if(GameModeAndPaths.Contains(SelectedGameMode))
            {
                FString GameModePath = GameModeAndPaths[SelectedGameMode];
                PathToLobby = FString::Printf(TEXT("%s?Game=%s"), *PathToLobby, *GameModePath);
            }

            World->ServerTravel(PathToLobby);
        }
    }
    else{
         if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Failed to create session")));
		}
        HostButton->SetIsEnabled(true);
    }
}

void UMainMenuWidget::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful) 
{
	if (MultiplayerSessionSubsystem == nullptr)
	{
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("No sub system")));
		return;
	}

	for (auto Result : SessionResults)
	{
		FString SettingsValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		if (SettingsValue == MatchType)
		{
            GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("trying to join a session")));
			MultiplayerSessionSubsystem->JoinSession(Result);
			return;
		}
	
		if(GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("Session Found ID: %s, User: %s"), *Id, *User));
		}
		if(MatchType == FString("FreeForAll"))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("Joining Match type %s"), *MatchType));
		}
	}
    if(!bWasSuccessful || SessionResults.Num() == 0)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("No session found")));
        JoinButton->SetIsEnabled(true);
    }
}

void UMainMenuWidget::OnJoinSession(EOnJoinSessionCompleteResult::Type Result) 
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if(Subsystem)
    {
        IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
        if(SessionInterface.IsValid())
        {
            FString Address;
            SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

            APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
            if(PlayerController)
            {
                PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
            }
        }
    }
    if(Result != EOnJoinSessionCompleteResult::Success)
    {
         GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("FAILED TO JOIN")));
        JoinButton->SetIsEnabled(true);
    }
}

void UMainMenuWidget::OnDestroySession(bool bWasSuccessful) 
{
	
}

void UMainMenuWidget::OnStartSession(bool bWasSuccessful) 
{
	
}
