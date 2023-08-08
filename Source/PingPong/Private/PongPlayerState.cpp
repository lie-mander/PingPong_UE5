// PingPong by Liemander

#include "PongPlayerState.h"
#include "Net/UnrealNetwork.h"

void APongPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APongPlayerState, Team);
}

FString APongPlayerState::GetTeamString() const
{
    if (Team == EPongTeam::EPT_RedTeam)
        return FString("RedTeam");
    else if (Team == EPongTeam::EPT_BlueTeam)
        return FString("BlueTeam");

    return FString();
}
