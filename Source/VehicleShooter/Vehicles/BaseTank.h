// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVehicle.h"
#include "BaseTank.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API ABaseTank : public ABaseVehicle
{
	GENERATED_BODY()
	
public:
	ABaseTank();

protected:
	//virtual void MoveForward(float InputValue) override;
	virtual void MoveRight(float InputValue) override;
	virtual void MoveForward(float InputValue);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UChaosVehicleMovementComponent> MovementComponent2;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UMaterialInstanceDynamic> TankTrackMI;
};
