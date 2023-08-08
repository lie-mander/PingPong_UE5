// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class APongGameMode;
class USoundCue;

UCLASS()
class PINGPONG_API APongBall : public AActor
{
    GENERATED_BODY()

public:
    APongBall();
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Pong | Components")
    UStaticMeshComponent* BallMesh;

    UPROPERTY(VisibleAnywhere, Category = "Pong | Components")
    UProjectileMovementComponent* Movement;

    UPROPERTY(EditDefaultsOnly, Category = "Pong | Sounds")
    USoundCue* BallHit;

    UPROPERTY()
    APongGameMode* PongGameMode;

    UFUNCTION(NetMulticast, Unreliable)
    void Multicast_UpdateTransformToClients(const FTransform& Transform);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_PlayHitSound();

    UFUNCTION()
    void OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& Hit);
};
