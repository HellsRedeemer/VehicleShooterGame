// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void UpdateHealthBar(float CurrentHealth, float MaxHealh);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;


};
