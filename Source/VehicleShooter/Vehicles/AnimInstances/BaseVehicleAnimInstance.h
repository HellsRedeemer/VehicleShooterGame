// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleAnimationInstance.h"

#include "BaseVehicleAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API UBaseVehicleAnimInstance : public UVehicleAnimationInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class ABaseVehicle* VehicleOwner;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float Speed;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FRotator GunLookingAtRotation;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UMaterialInstance* TankTrackMI;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float WheelSpeedOffset;

private:
};
