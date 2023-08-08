// PingPong by Liemander

#include "PongBall.h"
#include "PongPlayer.h"
#include "PongGates.h"
#include "PongGameMode.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

APongBall::APongBall()
{
    PrimaryActorTick.bCanEverTick = true;

    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
    BallMesh->SetEnableGravity(false);
    BallMesh->SetCollisionObjectType(ECC_WorldDynamic);
    BallMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
    BallMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    BallMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SetRootComponent(BallMesh);

    Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
    Movement->ProjectileGravityScale = 0.f;
    Movement->InitialSpeed = 300.f;
    Movement->MaxSpeed = 300.f;
    Movement->SetIsReplicated(true);
    bReplicates = true;
}

void APongBall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Multicast_UpdateTransformToClients(GetActorTransform());
}

void APongBall::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        BallMesh->OnComponentHit.AddDynamic(this, &APongBall::OnBallHit);
    }
}

void APongBall::OnBallHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    APongGates* Gates = Cast<APongGates>(OtherActor);
    if (Gates)
    {
        PongGameMode = !PongGameMode ? GetWorld()->GetAuthGameMode<APongGameMode>() : PongGameMode;
        if (PongGameMode)
        {
            PongGameMode->Goal(Gates->GetTeam());
        }
    }
    else
    {
        APongPlayer* Player = Cast<APongPlayer>(OtherActor);
        if (Player)
        {
            Multicast_PlayHitSound();
        }
    }
}

void APongBall::Multicast_PlayHitSound_Implementation()
{
    UGameplayStatics::PlaySoundAtLocation(this, BallHit, GetActorLocation());
}

void APongBall::Multicast_UpdateTransformToClients_Implementation(const FTransform& Transform)
{
    SetActorTransform(Transform);
}
