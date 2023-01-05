// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoinGameWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FJoinGameModeChosen, EGameModes, GameModeEnum);
/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API UJoinGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FJoinGameModeChosen GameModeChosenDelegate;

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
