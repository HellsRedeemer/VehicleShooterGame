// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "VehicleShooter/Types/Teams.h"

#include "VehicleShooterPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API AVehicleShooterPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void SetTeam(ETeams WhichTeam);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:

private:
	UPROPERTY(ReplicatedUsing = OnRep_Team)
	ETeams Team;

	UFUNCTION()
	void OnRep_Team();

public:
	FORCEINLINE ETeams GetTeam() const {return Team;}
	
};
