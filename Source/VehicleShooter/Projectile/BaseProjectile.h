// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class VEHICLESHOOTER_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class USceneComponent* BaseComponent;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	class UProjectileMovementComponent* MovementComp;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* ProjectileMesh;

	UFUNCTION()
	void ProjectileOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float Damage = 33.f;

public:	


};
