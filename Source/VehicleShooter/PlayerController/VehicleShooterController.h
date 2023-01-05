// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VehicleShooter/Types/Teams.h"
#include "VehicleShooterController.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API AVehicleShooterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void UpdateHUDScores(const TArray<ETeams> Teams, const TArray<uint32> TeamScores);

protected:

private:
	UPROPERTY()
	class ABaseGameModeHUD* GameHUD;
};
