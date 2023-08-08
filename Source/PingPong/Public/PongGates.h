// PingPong by Liemander

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongTypes.h"
#include "PongGates.generated.h"

class UBoxComponent;

UCLASS()
class PINGPONG_API APongGates : public AActor
{
    GENERATED_BODY()

public:
    APongGates();

    FORCEINLINE EPongTeam GetTeam() const { return GatesTeam; }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Pong | Components")
    UBoxComponent* GatesCollision;

    UPROPERTY(EditAnywhere, Category = "Pong | Gates")
    EPongTeam GatesTeam;
};
