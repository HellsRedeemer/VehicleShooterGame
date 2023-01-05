// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "Components/ProgressBar.h"

void UMainHUD::UpdateHealthBar(float CurrentHealth, float MaxHealh) 
{
    HealthBar->SetPercent(CurrentHealth / MaxHealh);
}
