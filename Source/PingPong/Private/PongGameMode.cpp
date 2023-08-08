// PingPong by Liemander

#include "PongGameMode.h"
#include "PongPlayerState.h"
#include "PongGameState.h"
#include "PongPlayerController.h"
#include "PongBall.h"

void APongGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    APongPlayerState* PongPlayerState = NewPlayer->GetPlayerState<APongPlayerState>();
    APongPlayerController* PongPlayerController = Cast<APongPlayerController>(NewPlayer);

    if (PongPlayerState && PongPlayerController && GetNumPlayers() == 1)
    {
        PongPlayerState->SetTeam(EPongTeam::EPT_RedTeam);
        PongPlayerController->ShowWaitingText(true);
        PongPlayerController->PlayMusicWaitStart();
        SpawnPlayerByTeam(PongPlayerController, PongPlayerState->GetTeamString());
    }
    else if (PongPlayerState && PongPlayerController && GetNumPlayers() == 2)
    {
        PongPlayerState->SetTeam(EPongTeam::EPT_BlueTeam);
        HideWaitingTextForAllPlayers();

        StartPingPong();
    }

    PongPlayerController->bPostLogin = true;
    RestartPlayer(PongPlayerController);
}

void APongGameMode::RestartPlayer(AController* NewPlayer)
{
    if (!NewPlayer) return;

    APongPlayerController* PongPlayerController = Cast<APongPlayerController>(NewPlayer);
    if (!PongPlayerController || !PongPlayerController->bPostLogin) return;

    APongPlayerState* PongPlayerState = PongPlayerController->GetPlayerState<APongPlayerState>();
    if (!PongPlayerState) return;

    RestartPlayerAtPlayerStart(PongPlayerController, GetPlayerStartByTeam(PongPlayerController, PongPlayerState->GetTeamString()));
}

void APongGameMode::Goal(EPongTeam TeamGoalTo)
{
    PongGameState = !PongGameState ? GetGameState<APongGameState>() : PongGameState;

    if (TeamGoalTo == EPongTeam::EPT_BlueTeam && PongGameState)
    {
        PongGameState->AddScore(EPongTeam::EPT_RedTeam);
        UpdateScoreForAllPlayers(PongGameState->GetRedScore(), PongGameState->GetBlueScore());
    }
    else if (TeamGoalTo == EPongTeam::EPT_RedTeam && PongGameState)
    {
        PongGameState->AddScore(EPongTeam::EPT_BlueTeam);
        UpdateScoreForAllPlayers(PongGameState->GetRedScore(), PongGameState->GetBlueScore());
    }

    RestartPingPong();
}

void APongGameMode::HideWaitingTextForAllPlayers()
{
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APongPlayerController* PlayerActor = Cast<APongPlayerController>(*Iterator);
        if (PlayerActor)
        {
            PlayerActor->ShowWaitingText(false);
        }
    }
}

void APongGameMode::UpdateScoreForAllPlayers(int32 RedScore, int32 BlueScore)
{
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APongPlayerController* PlayerActor = Cast<APongPlayerController>(*Iterator);
        if (PlayerActor)
        {
            PlayerActor->UpdateScore(RedScore, BlueScore);
        }
    }
}

void APongGameMode::PlayGameMusicForAllPlayers() 
{
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APongPlayerController* PlayerActor = Cast<APongPlayerController>(*Iterator);
        if (PlayerActor)
        {
            PlayerActor->PlayMusicGameStart();
        }
    }
}

void APongGameMode::SpawnAllPlayersByTeam()
{
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APongPlayerController* PlayerActor = Cast<APongPlayerController>(*Iterator);
        if (PlayerActor)
        {
            APongPlayerState* PongPlayerState = PlayerActor->GetPlayerState<APongPlayerState>();
            if (PongPlayerState)
            {
                SpawnPlayerByTeam(PlayerActor, PongPlayerState->GetTeamString());
            }
        }
    }
}

void APongGameMode::SpawnPlayerByTeam(AController* Player, const FString& Team)
{
    APongPlayerController* PongPlayerController = Cast<APongPlayerController>(Player);
    if (!PongPlayerController) return;

    AActor* PlayerStart = FindPlayerStart(PongPlayerController, Team);
    if (PlayerStart)
    {
        PongPlayerController->UpdateTransform(PlayerStart->GetActorTransform());
    }
}

void APongGameMode::StartPingPong()
{
    if (!GetWorld()) return;

    const int RandRotationIndex = FMath::RandRange(0, RandBallSpawnRotations.Num() - 1);
    PongBall = GetWorld()->SpawnActor<APongBall>(PongBallClass, BallSpawnLocation, RandBallSpawnRotations[RandRotationIndex]);

    SpawnAllPlayersByTeam();
    PlayGameMusicForAllPlayers();
}

void APongGameMode::RestartPingPong()
{
    if (PongBall)
    {
        PongBall->Destroy();
    }

    StartPingPong();
}

AActor* APongGameMode::GetPlayerStartByTeam(AController* Player, const FString& Team)
{
    if (!Player) return nullptr;

    AActor* PlayerStart = FindPlayerStart(Player, Team);
    if (PlayerStart)
    {
        return PlayerStart;
    }
    return nullptr;
}
