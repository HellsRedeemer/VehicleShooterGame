// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VehicleShooter/Types/GameModes.h"
#include "HostGameDetailsWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameModeChosen, EGameModes, GameModeEnum);
/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API UHostGameDetailsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FGameModeChosen GameModeSelectedDelegate;

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UGameModeSelectButton* DominationGameModeButton;
	UPROPERTY(meta = (BindWidget))
	class UGameModeSelectButton* ControlGameModeButton;
	UPROPERTY(meta = (BindWidget))
	class UGameModeSelectButton* TDMGameModeButton;

	
	UFUNCTION()
	void GameModeSelected(EGameModes GameModeEnum);
	
};
