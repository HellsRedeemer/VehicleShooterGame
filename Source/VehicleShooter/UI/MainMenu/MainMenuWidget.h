// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerSessionSubsystem.h"
#include "VehicleShooter/Types/GameModes.h"
#include "VehicleShooter/Types/GameModes.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString("FreeForAll"), FString LobbyPath = FString(TEXT("/Game/VehicleTemplate/Maps/VehicleExampleMap")));

protected:
	virtual bool Initialize() override;
	//virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	virtual void NativeDestruct() override;

	//callbacks for the custom delegates on the multiplayer sessions subsystem
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(Meta = (BindWidget))
	class UButton* JoinButton;
	

	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();

	class UMultiplayerSessionSubsystem* MultiplayerSessionSubsystem;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 NumPublicConnections = 4;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString MatchType = FString("FreeForAll");

	FString PathToLobby;


	//
	UPROPERTY(meta = (BindWidget))
	class UHostGameDetailsWidget* HostDetailsWidget;

	UFUNCTION()
	void GameModeSelected(EGameModes GameMode);

	UPROPERTY(meta = (BindWidget))
	class UJoinGameWidget* JoinGameWidget;

	UFUNCTION()
	void GameModeToJoinSelected(EGameModes GameMode);


	UPROPERTY(Meta = (BindWidget))
	class UButton* BackButton;
	UFUNCTION()
	void BackToMainMenu();

	UPROPERTY(Meta = (BindWidget))
	class UButton* QuitButton;
	UFUNCTION()
	void QuitGame();

	TMap<EGameModes, FString> GameModeAndPaths;
	EGameModes SelectedGameMode;
};
