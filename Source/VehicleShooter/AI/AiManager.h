// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AiManager.generated.h"

UCLASS()
class VEHICLESHOOTER_API AAiManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAiManager();
	void SpawnAi(const TArray<FTransform> Transforms, AActor* ParentToAttachTo);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class ABaseAi> AisToSpawnClass;

public:	


};
