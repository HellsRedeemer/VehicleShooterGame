// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVehicleAnimInstance.h"
#include "VehicleShooter/Vehicles/BaseVehicle.h"

void UBaseVehicleAnimInstance::NativeInitializeAnimation() 
{
    //Super::NativeInitializeAnimation();
    VehicleOwner = Cast<ABaseVehicle>(TryGetPawnOwner());
}

void UBaseVehicleAnimInstance::NativeUpdateAnimation(float DeltaTime) 
{
    Super::NativeUpdateAnimation(DeltaTime);

    if(VehicleOwner == nullptr)
    {
        VehicleOwner = Cast<ABaseVehicle>(TryGetPawnOwner());
    }
    if(VehicleOwner == nullptr) return;

    GunLookingAtRotation.Yaw = VehicleOwner->GetWeaponYaw();
    GunLookingAtRotation.Pitch = VehicleOwner->GetWeaponPitch();
    
    FVector Velocity = VehicleOwner->GetVelocity();
    Velocity.Z = 0.f;
    Speed = Velocity.Size();
    //WheelSpeedOffset = WheelSpeedOffset % 360.f;//(WheelSpeedOffset + DeltaTime);// % 360.0f;
}
