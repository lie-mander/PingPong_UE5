// PingPong by Liemander

#include "PongPlayer.h"
#include "PongGameMode.h"
#include "PongPlayerState.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

APongPlayer::APongPlayer()
{
    PrimaryActorTick.bCanEverTick = true;

    PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlayerMesh");
    PlayerMesh->SetEnableGravity(false);
    PlayerMesh->SetCollisionObjectType(ECC_Pawn);
    PlayerMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
    PlayerMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
    PlayerMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    PlayerMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SetRootComponent(PlayerMesh);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArm->SetupAttachment(PlayerMesh);

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);

    RedTeamMaterial = CreateDefaultSubobject<UMaterial>("RedTeamMaterial");
    BlueTeamMaterial = CreateDefaultSubobject<UMaterial>("BlueTeamMaterial");

    Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
    Movement->SetIsReplicated(true);
    bReplicates = true;
}

void APongPlayer::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        Multicast_SetTeamMaterial();
    }
}

void APongPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsLocallyControlled())
    {
        Server_UpdateTransform(GetActorTransform());
    }
}

void APongPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::OnMoveButtonPressed);
}

void APongPlayer::OnMoveButtonPressed(float Value)
{
    if (Value == 0.0f) return;

    AddMovementInput(GetActorRightVector(), Value);
}

void APongPlayer::Multicast_SetTeamMaterial_Implementation()
{
    APongPlayerState* PongPlayerState = GetPlayerState<APongPlayerState>();
    if (PongPlayerState && PlayerMesh)
    {
        if (PongPlayerState->GetTeam() == EPongTeam::EPT_RedTeam && RedTeamMaterial)
        {
            PlayerMesh->SetMaterial(0, RedTeamMaterial);
        }
        else if (PongPlayerState->GetTeam() == EPongTeam::EPT_BlueTeam && BlueTeamMaterial)
        {
            PlayerMesh->SetMaterial(0, BlueTeamMaterial);
        }
    }
}

void APongPlayer::Server_UpdateTransform_Implementation(const FTransform& Transform)
{
    SetActorTransform(Transform);
}
