// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VehicleShooter/Types/Teams.h"
#include "TeamsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTeamsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VEHICLESHOOTER_API ITeamsInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual ETeams GetTeam() const = 0;
};
