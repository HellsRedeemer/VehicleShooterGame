// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"



bool UMenu::Initialize() 
{
    if(!Super::Initialize())
    {
        return false;    
    }

    if(HostButton)
    {
        HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
    }
    if(JoinButton)
    {
        JoinButton->OnClicked.AddDynamic(this, &UMenu::JoinButtonClicked);
    }

	return true;
}

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch, FString LobbyPath) 
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
        MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &UMenu::OnCreateSession);
        MultiplayerSessionSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &UMenu::OnFindSessions);
        MultiplayerSessionSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &UMenu::OnJoinSession);
        MultiplayerSessionSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &UMenu::OnDestroySession);
        MultiplayerSessionSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &UMenu::OnStartSession);
    }
    

}

void UMenu::HostButtonClicked() 
{
    
    HostButton->SetIsEnabled(false);
	//UE_LOG(LogTemp, Warning, TEXT("Host button Clicked"));
    if(MultiplayerSessionSubsystem)
    {
        MultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
    }
}

void UMenu::JoinButtonClicked() 
{
    JoinButton->SetIsEnabled(false);
    if(MultiplayerSessionSubsystem)
    {
        MultiplayerSessionSubsystem->FindSessions(99999);
        //MultiplayerSessionSubsystem->JoinSession();
    }
}

void UMenu::NativeDestruct() 
{
    MenuTearDown();
    Super::NativeDestruct();
}

void UMenu::MenuTearDown() 
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

void UMenu::OnCreateSession(bool bWasSuccessful) 
{
	if(bWasSuccessful)
    {
        if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("session Created")));
		}
        
        UWorld* World = GetWorld();
        if(World)
        { 
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

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful) 
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

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result) 
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

void UMenu::OnDestroySession(bool bWasSuccessful) 
{
	
}

void UMenu::OnStartSession(bool bWasSuccessful) 
{
	
}
