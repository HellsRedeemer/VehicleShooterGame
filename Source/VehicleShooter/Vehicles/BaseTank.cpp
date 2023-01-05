// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTank.h"
//#include "ChaosVehicleMovementComponent.h"

#include "ChaosWheeledVehicleMovementComponent.h"

ABaseTank::ABaseTank() 
{
    GetVehicleMovementComponent()->TorqueControl.Enabled = true;
    GetVehicleMovementComponent()->TorqueControl.YawTorqueScaling = 3.0f;

    MovementComponent2 = CreateDefaultSubobject<UChaosVehicleMovementComponent, UChaosWheeledVehicleMovementComponent>(TEXT("movement 2"));
                        
    //MovementComponent2->TorqueControl.Enabled = true;
    //MovementComponent2->TorqueControl.YawTorqueScaling = 3.0f;
}

void ABaseTank::MoveRight(float InputValue) 
{

    if(InputValue > 0)
    {
        GetVehicleMovementComponent()->SetYawInput(1);
        MovementComponent2->SetYawInput(0);
    }
    else if(InputValue < 0)
    {
        GetVehicleMovementComponent()->SetYawInput(0);
        MovementComponent2->SetYawInput(1);
    }
    else
    {
        GetVehicleMovementComponent()->SetYawInput(0);
        MovementComponent2->SetYawInput(0);
    }
}

void ABaseTank::MoveForward(float InputValue) 
{

    if(InputValue >= 0)
    {
        GetVehicleMovementComponent()->SetThrottleInput(InputValue);
        MovementComponent2->SetThrottleInput(InputValue);
        GetVehicleMovementComponent()->SetBrakeInput(0);
        MovementComponent2->SetBrakeInput(0);

        //GetVehicleMovementComponent()->EngineSetup.MaxRPM = 3500;
        //MovementComponent2->EngineSetup.MaxRPM = 3500;
    }
    else
    {
        GetVehicleMovementComponent()->SetBrakeInput(InputValue * -1);
        MovementComponent2->SetBrakeInput(InputValue * -1);
        GetVehicleMovementComponent()->SetThrottleInput(0); 
        MovementComponent2->SetThrottleInput(0); 

        //GetVehicleMovementComponent()->EngineSetup.MaxRPM = 2000;
        //MovementComponent2->EngineSetup.MaxRPM = 2000;
    }
}

