// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VehicleShooter/Types/Teams.h"
//
#include "BaseGameModeHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishedSetup);
/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API ABaseGameModeHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void UpdateTeamScore(const TArray<ETeams> Teams, const TArray<uint32> Scores);
	FFinishedSetup FinishedSetup;
	void TogglePauseMenu();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	TSubclassOf<class UMainHUD> MainUIClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	TSubclassOf<class UPauseWidget> PauseWidgetClass;

	UPROPERTY()
	class UPauseWidget* PauseWidget;
	UPROPERTY()
	class UMainHUD* MainHUD;

public:
	FORCEINLINE UMainHUD* GetMainHUD() const {return MainHUD;}
};
