// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "VehicleShooter/Types/Teams.h"
#include "VehicleShooter/Interfaces/TeamsInterface.h"
#include "VehicleShooter/Interfaces/VehicleInterface.h"


#include "BaseVehicle.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESHOOTER_API ABaseVehicle : public AWheeledVehiclePawn, public ITeamsInterface, public IVehicleInterface
{
	GENERATED_BODY()
	

public:
	ABaseVehicle();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PossessedBy(AController* NewController) override;
	//interfaces
	virtual ETeams GetTeam() const override;
	const TArray<FTransform> GetAiSpawnTransformsInVehilce() const override;

protected:

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void MoveForward(float InputValue);
	virtual void MoveRight(float InputValue);
	void LookUp(float InputVal);
	void LookRight(float InputVal);
	virtual void PollInit();
	UFUNCTION(BlueprintImplementableEvent)
	void SetTeamColours();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UCameraComponent> MainCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ETeams Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UHealthComponent> HealthComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UWeaponComponent> WeaponComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> FiringPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> AiSpawnLocationsParent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName FiringSocketName = FName("FiringPointSocket");

	UFUNCTION()
	void DamagedRecieved(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION()
	void WasDamaged(float Damage, float NewHealthValue);
	UFUNCTION(Client, Reliable)
	void Client_HealthChanged(float NewHealth);

	void FireWeapon();

	void CalculateWeaponRot();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Anims, meta = (AllowPrivateAccess = true))
	float MaxWeaponPitch = 35.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Anims, meta = (AllowPrivateAccess = true))
	float MinWeaponPitch = -12.5f;
	
	UPROPERTY(Replicated)
	float WeaponPitch;
	UPROPERTY(Replicated)
	float WeaponYaw;

	class ABaseGameModeHUD* MyHUD;
	UFUNCTION()
	void HUDFinshedSetup();

	UPROPERTY()
	class AVehicleShooterPlayerState* MyPlayerState;


	
	UFUNCTION()
	void TogglePauseMenu();

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true));
	uint8 AmountOfAiSeats = 2;

public:
	void SetTeam(ETeams WhichTeam);
	FORCEINLINE float GetWeaponPitch() {return WeaponPitch;}
	FORCEINLINE float GetWeaponYaw() {return WeaponYaw;}
};
