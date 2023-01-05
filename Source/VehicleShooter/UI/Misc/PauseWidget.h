// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;	

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* ControlsButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

	UFUNCTION()
	void QuitGame();
	UFUNCTION()
	void MainMenu();
};
