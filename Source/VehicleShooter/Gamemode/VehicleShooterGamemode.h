// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VehicleShooter/Types/Teams.h"
#include "VehicleShooter/AI/AiManager.h"

#include "VehicleShooterGamemode.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API AVehicleShooterGamemode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AVehicleShooterGamemode();

	virtual void RequestRespawn(class APawn* PawnToDestroy, class AController* ControllerRespawning);
	virtual void RespawnPawn(TSubclassOf<APawn> PawnClassToSpawn, AController* ControllerRespawning, AActor* PlayerStartToSpawnAt);

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
protected:
	

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bUseTeams = true;

	UPROPERTY()
	class AAiManager* AiManager;
};
