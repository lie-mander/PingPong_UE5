// PingPong by Liemander

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PongTypes.h"
#include "PongPlayerState.generated.h"

UCLASS()
class PINGPONG_API APongPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    FORCEINLINE EPongTeam GetTeam() const { return Team; }
    FORCEINLINE void SetTeam(EPongTeam NewTeam) { Team = NewTeam; }
    FString GetTeamString() const;

private:
    UPROPERTY(VisibleAnywhere, Replicated)
    EPongTeam Team;
};
