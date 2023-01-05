// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleShooter/UI/GameMode/BaseGameModeHUD.h"
#include "ControlGameModeHUD.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API AControlGameModeHUD : public ABaseGameModeHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UControlWidget> ControlWidgetClass;

	UPROPERTY()
	class UControlWidget* ControlWidget;
};
