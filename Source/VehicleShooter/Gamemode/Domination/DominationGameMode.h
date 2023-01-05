// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleShooter/Gamemode/VehicleShooterGamemode.h"
#include "DominationGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API ADominationGameMode : public AVehicleShooterGamemode
{
	GENERATED_BODY()
	
public:

protected:
	virtual void BeginPlay() override;

private:
	TArray<class ADominationFlag*> DominationFlags;

	UFUNCTION()
	void DominationFlagCaptured(ETeams TeamThatCaptured, ETeams TeamThatLostFlag);
	void DominationFlagLost(ETeams TeamThatLostFlag);
	
	TMap<ETeams, int32> TeamsAndFlagCount;
	TMap<ETeams, int32> TeamsAndScore;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float TimeBetweenPointGained = 3.f;
	FTimerHandle AddCaptureScoreHandle;
	void AddScore();
};
