// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VehicleShooter/Types/Teams.h"
#include "DominationFlag.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFlagCaptured, ETeams, TeamThatCapturedFlag, ETeams, TeamThatLostFlag);

UCLASS()
class VEHICLESHOOTER_API ADominationFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	ADominationFlag();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFlag(float CapurePercent, ETeams OwnerTeam, ETeams CapturingTeam);

	FFlagCaptured FlagCaptureDelegate;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* FlagMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USphereComponent* CaptureCollision;

	UFUNCTION()
	void CaptureCollisionEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void CaptureCollisionLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ETeams OwningTeam;
	
	TMap<ETeams, int32> TeamMemberInCaptureZone;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float TimeToCap = 3.0f;
	float CapTimeLeft = 1.0f;
	FTimerHandle CaptureHandle;
	float UpdateSpeed = 0.1f;
	ETeams CurrentlyCapturingTeam = ETeams::ET_NoTeam;
	UFUNCTION()
	void UpdateFlagCapturePercent();

	void StopCaptureProgress();

	void CheckIfCanCapture(ETeams TeamEntered);
	void PlayerLeftCheckForCapture(ETeams TeamLeft);

public:	
	


};
