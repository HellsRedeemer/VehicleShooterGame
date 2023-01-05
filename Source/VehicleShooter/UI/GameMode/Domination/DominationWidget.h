// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VehicleShooter/Types/Teams.h"
#include "DominationWidget.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API UDominationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateTeamScores(const TArray<ETeams> Teams, const TArray<uint32> Scores);

protected:

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RedTeamScore;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BlueTeamScore;
};
