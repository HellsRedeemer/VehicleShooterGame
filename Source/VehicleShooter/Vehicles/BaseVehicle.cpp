// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVehicle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "VehicleShooter/Components/HealthComponent.h"
#include "VehicleShooter/Components/WeaponComponent.h"
#include "Net/UnrealNetwork.h"
#include "VehicleShooter/UI/GameMode/BaseGameModeHUD.h"
#include "VehicleShooter/UI/Vehicle/MainHUD.h"
#include "VehicleShooter/PlayerStates/VehicleShooterPlayerState.h"
	#include "Kismet/KismetMathLibrary.h"


ABaseVehicle::ABaseVehicle() 
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    //SpringArm->SetupAttachment(GetMesh(), FName("CameraSocket"));
    SpringArm->SetupAttachment(RootComponent);

    MainCamera = CreateDefaultSubobject<UCameraComponent>("Main Camera");
    MainCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

    HealthComp = CreateDefaultSubobject<UHealthComponent>("Health Component");
    if(HealthComp)
    {
        HealthComp->WasDamagedDelegate.AddUniqueDynamic(this, &ABaseVehicle::WasDamaged);
    }

    FiringPoint = CreateDefaultSubobject<USceneComponent>("Firing Point");
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
    //FiringPoint->AttachToComponent(RootComponent, AttachmentRules, FiringSocketName);
    FiringPoint->SetupAttachment(RootComponent, FiringSocketName);

    WeaponComp = CreateDefaultSubobject<UWeaponComponent>("Weapon Comp");
    WeaponComp->FiringPoint = FiringPoint;

    AiSpawnLocationsParent = CreateDefaultSubobject<USceneComponent>("AiSpawnLocationParent");
    AiSpawnLocationsParent->SetupAttachment(GetMesh());
}

void ABaseVehicle::BeginPlay() 
{
    Super::BeginPlay();
    if(HealthComp)
    {
        APlayerController* PController = Cast<APlayerController>(GetController());
        if(PController)
        {
            
            MyHUD = Cast<ABaseGameModeHUD>(PController->GetHUD());
            if(MyHUD && !MyHUD->GetMainHUD())
            {
                MyHUD->FinishedSetup.AddDynamic(this, &ABaseVehicle::HUDFinshedSetup);
            }
            else if(MyHUD && MyHUD->GetMainHUD())
            {
                MyHUD->GetMainHUD()->UpdateHealthBar(HealthComp->GetCurrentHealth(), HealthComp->GetMaxHealth());
            }
        }
    }

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
    FiringPoint->AttachToComponent(RootComponent, AttachmentRules, FiringSocketName);
    OnTakeAnyDamage.AddUniqueDynamic(this, &ABaseVehicle::DamagedRecieved);
}

void ABaseVehicle::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    CalculateWeaponRot();
    PollInit();
    /*if(TankTrackMI)
    {
        TankTrackMI->SetScalarParameterValue(FName("OffsetV"), 1.f);
    }*/

   // UE_LOG(LogTemp, Warning, TEXT(" PITCH IS: %i"), RemoteViewPitch);
}

void ABaseVehicle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(ABaseVehicle, WeaponYaw, COND_SkipOwner);
    DOREPLIFETIME_CONDITION(ABaseVehicle, WeaponPitch, COND_SkipOwner);
}

void ABaseVehicle::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ABaseVehicle::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABaseVehicle::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ABaseVehicle::LookUp);
    PlayerInputComponent->BindAxis("LookRight", this, &ABaseVehicle::LookRight);

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABaseVehicle::FireWeapon);
    PlayerInputComponent->BindAction("TogglePauseMenu", IE_Pressed, this, &ABaseVehicle::TogglePauseMenu);
}

void ABaseVehicle::PossessedBy(AController* NewController) 
{
    Super::PossessedBy(NewController);
    if(HealthComp)
    {
        APlayerController* PController = Cast<APlayerController>(GetController());
        if(PController)
        {
            MyHUD = Cast<ABaseGameModeHUD>(PController->GetHUD());
            if(MyHUD && !MyHUD->GetMainHUD())
            {
                MyHUD->FinishedSetup.AddDynamic(this, &ABaseVehicle::HUDFinshedSetup);
            }
            else if(MyHUD && MyHUD->GetMainHUD())
            {
                MyHUD->GetMainHUD()->UpdateHealthBar(HealthComp->GetCurrentHealth(), HealthComp->GetMaxHealth());
            }
        }
    }
}

void ABaseVehicle::PollInit() 
{
    if(MyPlayerState == nullptr)
    {
        MyPlayerState = GetPlayerState<AVehicleShooterPlayerState>();
        if(MyPlayerState)
        {
            Team = MyPlayerState->GetTeam();
            SetTeamColours();
            UE_LOG(LogTemp, Warning, TEXT("TEAM HAS BEEN SET"));
        }
    }
}

void ABaseVehicle::HUDFinshedSetup() 
{
    if(MyHUD && MyHUD->GetMainHUD() && HealthComp)
    {
        MyHUD->GetMainHUD()->UpdateHealthBar(HealthComp->GetCurrentHealth(), HealthComp->GetMaxHealth());
    }
}

void ABaseVehicle::TogglePauseMenu() 
{
    if(MyHUD)
    {
        MyHUD->TogglePauseMenu();
    }
}

void ABaseVehicle::SetTeam(ETeams WhichTeam) 
{
    Team = WhichTeam;
    SetTeamColours();
}


ETeams ABaseVehicle::GetTeam() const
{
    return Team;
}

const TArray<FTransform> ABaseVehicle::GetAiSpawnTransformsInVehilce() const 
{
    TArray<FTransform> Transforms;
    TArray<USceneComponent*> FoundChildren;
    AiSpawnLocationsParent->GetChildrenComponents(true, FoundChildren);
    for(USceneComponent* Child : FoundChildren)
    {   
        FTransform ChildTrans;
        ChildTrans.SetLocation(FVector(Child->GetRelativeLocation().Y, Child->GetRelativeLocation().X, Child->GetRelativeLocation().Z) + GetActorLocation());
        ChildTrans.SetRotation(FQuat(Child->GetRelativeRotation()));
        ChildTrans.SetScale3D(FVector(1,1,1));
        Transforms.Add(ChildTrans);
    }
    return Transforms;
}





void ABaseVehicle::MoveForward(float InputValue) 
{
    if(InputValue >= 0)
    {
        GetVehicleMovementComponent()->SetThrottleInput(InputValue);
        GetVehicleMovementComponent()->SetBrakeInput(0);
    }
    else
    {
        GetVehicleMovementComponent()->SetBrakeInput(InputValue * -1);
        GetVehicleMovementComponent()->SetThrottleInput(0); 
    }

   // UE_LOG(LogTemp, Warning, TEXT("INPUT IS: %f"), InputValue);
}

void ABaseVehicle::MoveRight(float InputValue) 
{
    GetVehicleMovementComponent()->SetYawInput(InputValue);
}

void ABaseVehicle::LookUp(float InputVal) 
{
    if(UKismetMathLibrary::InRange_FloatFloat(SpringArm->GetRelativeRotation().Pitch + InputVal, -30.f, 20.f))
    {
        SpringArm->AddRelativeRotation(FRotator(InputVal, 0, 0));
    } 
}

void ABaseVehicle::LookRight(float InputVal) 
{
    SpringArm->AddRelativeRotation(FRotator(0, InputVal, 0));
}

void ABaseVehicle::DamagedRecieved(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) 
{
    UE_LOG(LogTemp, Warning, TEXT("any damage event"));
    if(HealthComp)
    {
        HealthComp->DoDamage(Damage, DamageCauser, InstigatedBy);
    }
}

void ABaseVehicle::WasDamaged(float Damage, float NewHealthValue) 
{
    if(HealthComp && MyHUD && MyHUD->GetMainHUD())
    {
        MyHUD->GetMainHUD()->UpdateHealthBar(NewHealthValue, HealthComp->GetMaxHealth());
    }
    if(HasAuthority())
    {
        Client_HealthChanged(NewHealthValue);
    }
    UE_LOG(LogTemp, Warning, TEXT("DAMAGE CAME THROUGH"));
}

void ABaseVehicle::Client_HealthChanged_Implementation(float NewHealth) 
{
    if(HealthComp && MyHUD && MyHUD->GetMainHUD())
    {
        MyHUD->GetMainHUD()->UpdateHealthBar(NewHealth, HealthComp->GetMaxHealth());
    }
}

void ABaseVehicle::FireWeapon() 
{
    if(WeaponComp)
    {
        WeaponComp->FireWeapon();
    }
}

void ABaseVehicle::CalculateWeaponRot() 
{
    if(HasAuthority() || IsLocallyControlled())
    {   
        WeaponYaw = GetBaseAimRotation().Yaw - GetActorRotation().Yaw; //- ogspawn;// - GetBaseAimRotation().Yaw;//+ (GetActorRotation().Yaw / 2);
        WeaponPitch = FMath::ClampAngle(GetBaseAimRotation().Pitch, MinWeaponPitch, MaxWeaponPitch);
        //RepWeaponYaw = WeaponYaw;
    }
    //UE_LOG(LogTemp, Warning, TEXT("ROT IS %f"), WeaponYaw);
    if(WeaponYaw > 90.f && !IsLocallyControlled())
	{
		//could map it instead
		//WeaponYaw -= 360;
	}
}


