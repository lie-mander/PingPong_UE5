// PingPong by Liemander

#include "PongGameState.h"

void APongGameState::AddScore(EPongTeam Team) 
{
    if (Team == EPongTeam::EPT_RedTeam)
    {
        ++RedScore;
    }
    else if (Team == EPongTeam::EPT_BlueTeam)
    {
        ++BlueScore;
    }
}
