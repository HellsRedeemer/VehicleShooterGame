// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "VehicleShooter/Types/Teams.h"
#include "VehicleShooter/PlayerStates/VehicleShooterPlayerState.h"

#include "VehicleShooterGameState.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API AVehicleShooterGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void TeamScored(ETeams TeamWhichScored, uint32 NewScore);

	TArray<AVehicleShooterPlayerState*> NoTeamMemeber;
	TArray<AVehicleShooterPlayerState*> BlueTeamMemeber;
	TArray<AVehicleShooterPlayerState*> RedTeamMemeber;
protected:

private:
	UPROPERTY(Replicated)
	TArray<ETeams> Teams;
	UPROPERTY(ReplicatedUsing = OnRep_TeamsScores)
	TArray<uint32> TeamsScores;

	UFUNCTION()
	void OnRep_TeamsScores();
};
