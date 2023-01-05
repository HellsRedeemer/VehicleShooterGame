// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleShooterGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "VehicleShooter/GameState/VehicleShooterGameState.h"
#include "Kismet/GameplayStatics.h"
#include "VehicleShooter/Interfaces/VehicleInterface.h"
#include "VehicleShooter/PlayerStates/VehicleShooterPlayerState.h"


AVehicleShooterGamemode::AVehicleShooterGamemode() 
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(this, AAiManager::StaticClass(),FoundActors);
    if(FoundActors.Num() > 0)
    {
        AiManager = Cast<AAiManager>(FoundActors[0]);
    }
    //AiManager 
}

void AVehicleShooterGamemode::RequestRespawn(APawn* PawnToDestroy, AController* ControllerRespawning) 
{

    if(ControllerRespawning)
    {   
        TArray<AActor*> PlayerStarts;
        UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
        if(PlayerStarts.Num() > 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("RESPAWN at: %s"), *PlayerStarts[0]->GetName());
            //RestartPlayerAtPlayerStart(ControllerRespawning, PlayerStarts[0]);

            if(PawnToDestroy)
            {
                RespawnPawn(PawnToDestroy->GetClass(), ControllerRespawning, PlayerStarts[0]);
                PawnToDestroy->Destroy();
            }
        }
    }
}

void AVehicleShooterGamemode::RespawnPawn(TSubclassOf<APawn> PawnClassToSpawn, AController* ControllerRespawning, AActor* PlayerStartToSpawnAt) 
{
    if(!PawnClassToSpawn || PlayerStartToSpawnAt == nullptr) return;
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
   // SpawnParams.bNoFail = true;

    APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnClassToSpawn, PlayerStartToSpawnAt->GetActorLocation(), PlayerStartToSpawnAt->GetActorRotation(), SpawnParams);
    if(ControllerRespawning && SpawnedPawn)
    {
        ControllerRespawning->Possess(SpawnedPawn);
    }

    if(AiManager && SpawnedPawn)
    {   
        IVehicleInterface* VehicleInterface = Cast<IVehicleInterface>(SpawnedPawn);
	    if(VehicleInterface)
	    {   
            TArray<FTransform> SpawnLocations = VehicleInterface->GetAiSpawnTransformsInVehilce();
            //AActor& PawnRef = *SpawnedPawn;
            AiManager->SpawnAi(SpawnLocations, SpawnedPawn);
        }
    }
}

void AVehicleShooterGamemode::PostLogin(APlayerController* NewPlayer) 
{
    Super::PostLogin(NewPlayer);
    AVehicleShooterGameState* MyGameState = Cast<AVehicleShooterGameState>(UGameplayStatics::GetGameState(this));
    if(MyGameState)
    {
        AVehicleShooterPlayerState* PlayerState = NewPlayer->GetPlayerState<AVehicleShooterPlayerState>();
        if(PlayerState)
        {
            if(bUseTeams)
            {   
                if(MyGameState->BlueTeamMemeber.Num() >= MyGameState->RedTeamMemeber.Num())
                {
                    MyGameState->RedTeamMemeber.AddUnique(PlayerState);
                    PlayerState->SetTeam(ETeams::ET_RedTeam);
                    // UE_LOG(LogTemp, Warning, TEXT("BLUE"));
                }
                else
                {
                    MyGameState->BlueTeamMemeber.AddUnique(PlayerState);
                    PlayerState->SetTeam(ETeams::ET_BlueTeam);
                     //  UE_LOG(LogTemp, Warning, TEXT("RED"));
                }
            }
            else
            {
                MyGameState->NoTeamMemeber.AddUnique(PlayerState);
            }
        }
    }
    

}

void AVehicleShooterGamemode::Logout(AController* Exiting) 
{
    
}


