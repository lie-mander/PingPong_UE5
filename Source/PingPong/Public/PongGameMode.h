// PingPong by Liemander

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongTypes.h"
#include "PongGameMode.generated.h"

class APongBall;
class APongGameState;

UCLASS()
class PINGPONG_API APongGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void RestartPlayer(AController* NewPlayer) override;

    void SpawnPlayerByTeam(AController* Player, const FString& Team);
    void Goal(EPongTeam TeamGoalTo);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Pong | Properties")
    FVector BallSpawnLocation = FVector(0.f, 0.f, 140.f);
    UPROPERTY(EditDefaultsOnly, Category = "Pong | Properties")
    TArray<FRotator> RandBallSpawnRotations = {
        FRotator(0.f, 20.f, 0.f),   //
        FRotator(0.f, 40.f, 0.f),   //
        FRotator(0.f, 60.f, 0.f),   //
        FRotator(0.f, 120.f, 0.f),  //
        FRotator(0.f, 140.f, 0.f),  //
        FRotator(0.f, 160.f, 0.f),  //
        FRotator(0.f, 200.f, 0.f),  //
        FRotator(0.f, 220.f, 0.f),  //
        FRotator(0.f, 240.f, 0.f),  //
        FRotator(0.f, 300.f, 0.f),  //
        FRotator(0.f, 320.f, 0.f),  //
        FRotator(0.f, 340.f, 0.f),  //
    };

    UPROPERTY(EditDefaultsOnly, Category = "Pong | Properties")
    TSubclassOf<APongBall> PongBallClass;

    UPROPERTY()
    APongGameState* PongGameState;

    UPROPERTY()
    APongBall* PongBall;

    AActor* GetPlayerStartByTeam(AController* Player, const FString& Team);
    void HideWaitingTextForAllPlayers();
    void UpdateScoreForAllPlayers(int32 RedScore, int32 BlueScore);
    void PlayGameMusicForAllPlayers();
    void SpawnAllPlayersByTeam();
    void StartPingPong();
    void RestartPingPong();
};
