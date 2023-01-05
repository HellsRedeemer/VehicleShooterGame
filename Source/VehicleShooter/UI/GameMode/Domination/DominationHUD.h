// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleShooter/UI/GameMode/BaseGameModeHUD.h"
#include "DominationHUD.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API ADominationHUD : public ABaseGameModeHUD
{
	GENERATED_BODY()
	
public:
	virtual void UpdateTeamScore(const TArray<ETeams> Teams, const TArray<uint32> Scores) override;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UDominationWidget> DominationWidgetClass;

	UPROPERTY()
	class UDominationWidget* DominationWidget;
};
