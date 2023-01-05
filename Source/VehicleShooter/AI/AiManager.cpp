// Fill out your copyright notice in the Description page of Project Settings.


#include "AiManager.h"

#include "BaseAi.h"

// Sets default values
AAiManager::AAiManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAiManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAiManager::SpawnAi(const TArray<FTransform> Transforms, AActor* ParentToAttachTo) 
{
	if(!AisToSpawnClass)
	{
		return;
	}

	for(FTransform Transform : Transforms)
	{
		//UE_LOG(LogTemp, Warning, TEXT("TRY SPAWN AI"));
		ABaseAi* SpawnedAi = GetWorld()->SpawnActor<ABaseAi>(AisToSpawnClass, Transform);
		if(SpawnedAi && ParentToAttachTo)
		{
			FAttachmentTransformRules TransformsRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
			
			SpawnedAi->AttachToActor(ParentToAttachTo, TransformsRules, FName());
		}
		
	}
}

