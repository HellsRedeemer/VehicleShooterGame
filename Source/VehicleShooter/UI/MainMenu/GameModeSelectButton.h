// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VehicleShooter/Types/GameModes.h"
#include "GameModeSelectButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameModeSelected, EGameModes, WhichGameMode);
/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API UGameModeSelectButton : public UUserWidget
{
	GENERATED_BODY()

public:
	FGameModeSelected GameModeSelectedDelegate;

protected:
	virtual bool Initialize() override;	


private:
	UPROPERTY(meta = (BindWidget))
	class UButton* GameModeButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameModeTextBlock;



	UFUNCTION()
	void GameModeButtonPressed();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	EGameModes WhichGameMode;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	FText ButtonText;
};
