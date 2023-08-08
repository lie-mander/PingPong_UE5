// PingPong by Liemander

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

class APongHUD;
class USoundCue;
class UAudioComponent;

UCLASS()
class PINGPONG_API APongPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    void ShowWaitingText(bool bShow);
    void UpdateScore(int32 RedScore, int32 BlueScore);
    void UpdateTransform(const FTransform& NewTransform);
    void PlayMusicWaitStart();
    void PlayMusicGameStart();

    void Tick(float DeltaTime) override;

    bool bPostLogin = false;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    APongHUD* HUD;

    UPROPERTY(EditDefaultsOnly, Category = "Pong | Sounds")
    USoundCue* WaitStart;

    UPROPERTY()
    UAudioComponent* WaitStartComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Pong | Sounds")
    USoundCue* GameStart;

    UPROPERTY()
    UAudioComponent* GameStartComponent;

    bool bDelayWaitStartMusic = false;
    bool bDelayGameStartMusic = false;
    bool bDelayTransform = false;
    FTransform DelayTransform;

    UFUNCTION(Client, Reliable)
    void Client_PlayMusicWaitStart();

    UFUNCTION(Client, Reliable)
    void Client_PlayMusicGameStart();

    UFUNCTION(Client, Reliable)
    void Client_ShowWaitingText(bool bShow);

    UFUNCTION(Client, Reliable)
    void Client_UpdateScore(int32 RedScore, int32 BlueScore);

    UFUNCTION(Client, Reliable)
    void Client_UpdateTransform(const FTransform& NewTransform);

    void AddOverlay();
    void DelayInit();
};
