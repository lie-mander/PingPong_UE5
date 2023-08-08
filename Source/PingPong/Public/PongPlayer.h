// PingPong by Liemander

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PongPlayer.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UFloatingPawnMovement;
class USceneComponent;
class UMaterialInterface; 

UCLASS()
class PINGPONG_API APongPlayer : public APawn
{
    GENERATED_BODY()

public:
    APongPlayer();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Pong | Components")
    UStaticMeshComponent* PlayerMesh;

    UPROPERTY(VisibleAnywhere, Category = "Pong | Components")
    UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, Category = "Pong | Components")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, Category = "Pong | Components")
    UFloatingPawnMovement* Movement;

    UPROPERTY(EditDefaultsOnly, Category = "Pong | Materials")
    UMaterial* RedTeamMaterial;

    UPROPERTY(EditDefaultsOnly, Category = "Pong | Materials")
    UMaterial* BlueTeamMaterial;

    void OnMoveButtonPressed(float Value);

    UFUNCTION(Server, Unreliable)
    void Server_UpdateTransform(const FTransform& Transform);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_SetTeamMaterial();
};
