// Fill out your copyright notice in the Description page of Project Settings.


#include "DominationFlag.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "VehicleShooter/Interfaces/TeamsInterface.h"

// Sets default values
ADominationFlag::ADominationFlag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CaptureCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Capture Collision"));
	SetRootComponent(CaptureCollision);

	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	FlagMesh->SetupAttachment(CaptureCollision);
}	

// Called when the game starts or when spawned
void ADominationFlag::BeginPlay()
{
	Super::BeginPlay();
	if(CaptureCollision)
	{
		CaptureCollision->OnComponentBeginOverlap.AddDynamic(this, &ADominationFlag::CaptureCollisionEntered);
		CaptureCollision->OnComponentEndOverlap.AddDynamic(this, &ADominationFlag::CaptureCollisionLeft);
	}
}

void ADominationFlag::CaptureCollisionEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	
	if(OtherActor == nullptr) return;

	ITeamsInterface* TeamsInterface = Cast<ITeamsInterface>(OtherActor);
	if(TeamsInterface)
	{
		ETeams EnteredTeam = TeamsInterface->GetTeam();
		if(EnteredTeam != ETeams::ET_NoTeam)
		{
			CheckIfCanCapture(EnteredTeam);

			TeamMemberInCaptureZone.Add(EnteredTeam) += 1;
			//UE_LOG(LogTemp, Warning, TEXT("Player in cap zone is now: %i"), TeamMemberInCaptureZone.Num())
		}
	}
}

void ADominationFlag::CaptureCollisionLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	UE_LOG(LogTemp, Warning, TEXT("left zone"));
	if(OtherActor == nullptr) return;

	ITeamsInterface* TeamsInterface = Cast<ITeamsInterface>(OtherActor);
	if(TeamsInterface && TeamsInterface->GetTeam() != ETeams::ET_NoTeam)
	{
		if(TeamMemberInCaptureZone.Contains(TeamsInterface->GetTeam()))
		{
			TeamMemberInCaptureZone.Add(TeamsInterface->GetTeam()) = FMath::Clamp(TeamMemberInCaptureZone[TeamsInterface->GetTeam()] - 1, 0, 9999);
			PlayerLeftCheckForCapture(TeamsInterface->GetTeam());
		}

		//UE_LOG(LogTemp, Warning, TEXT("Player in cap zone is now: %i"), TeamMemberInCaptureZone.Num())
	}
}

void ADominationFlag::CheckIfCanCapture(ETeams TeamEntered) 
{
	if(TeamEntered != ETeams::ET_NoTeam || TeamEntered != OwningTeam)
	{	
		bool bCanCapture = true;
		for(auto Member : TeamMemberInCaptureZone)
		{
			if(Member.Key != TeamEntered && Member.Value > 0)
			{
				bCanCapture = false;
			}	
		}
		if(bCanCapture)
		{
			CapTimeLeft = TimeToCap;
			GetWorldTimerManager().SetTimer(CaptureHandle, this, &ADominationFlag::UpdateFlagCapturePercent, UpdateSpeed, true);
			CurrentlyCapturingTeam = TeamEntered;
			UE_LOG(LogTemp, Warning, TEXT("Start cap"));
		}
	}
	if(TeamEntered != CurrentlyCapturingTeam)
	{
		StopCaptureProgress();
	}
}

void ADominationFlag::PlayerLeftCheckForCapture(ETeams TeamLeft) 
{
	ETeams NewOwningTeam = ETeams::ET_NoTeam;
	bool bThisTeamCanCap = true;
	for(auto Member : TeamMemberInCaptureZone)
	{
		if(Member.Value > 0)
		{	
			//Check if this team can cap
			NewOwningTeam = Member.Key;
			
			for(auto Player : TeamMemberInCaptureZone)
			{
				if(Player.Key != Member.Key && Player.Value > 0)
				{
					bThisTeamCanCap = false;
				}
			}
		}
		else if(CurrentlyCapturingTeam == Member.Key)
		{
			StopCaptureProgress();
		}
	}

	if(bThisTeamCanCap && NewOwningTeam != ETeams::ET_NoTeam)
	{
		CapTimeLeft = TimeToCap;
		GetWorldTimerManager().SetTimer(CaptureHandle, this, &ADominationFlag::UpdateFlagCapturePercent, UpdateSpeed, true);
		CurrentlyCapturingTeam = NewOwningTeam;
		UE_LOG(LogTemp, Warning, TEXT("Start cap"));
	}

}

void ADominationFlag::UpdateFlagCapturePercent() 
{
	CapTimeLeft -= UpdateSpeed;
	//UE_LOG(LogTemp, Warning, TEXT("CAPTURE TIME LEFT: %f"), CapTimeLeft);
	UpdateFlag(CapTimeLeft / TimeToCap, OwningTeam, CurrentlyCapturingTeam);

	if(CapTimeLeft <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("CAPTURRED"));
		FlagCaptureDelegate.Broadcast(CurrentlyCapturingTeam, OwningTeam);
		OwningTeam = CurrentlyCapturingTeam;
		GetWorldTimerManager().ClearTimer(CaptureHandle);
		UpdateFlag(CapTimeLeft / TimeToCap, OwningTeam, CurrentlyCapturingTeam);
	}
}

void ADominationFlag::StopCaptureProgress() 
{
	GetWorldTimerManager().ClearTimer(CaptureHandle);
	CurrentlyCapturingTeam = ETeams::ET_NoTeam;
	UpdateFlag(CapTimeLeft / TimeToCap, OwningTeam, CurrentlyCapturingTeam);
}

// Called every frame
void ADominationFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

