// PingPong by Liemander

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongTypes.h"
#include "PongGameState.generated.h"

UCLASS()
class PINGPONG_API APongGameState : public AGameStateBase
{
    GENERATED_BODY()

public: 
    void AddScore(EPongTeam Team);

    FORCEINLINE int32 GetRedScore() const { return RedScore; }
    FORCEINLINE int32 GetBlueScore() const { return BlueScore; }

private:
    int32 RedScore = 0;
    int32 BlueScore = 0;
};
