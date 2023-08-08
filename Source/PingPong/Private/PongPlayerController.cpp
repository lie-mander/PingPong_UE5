// PingPong by Liemander

#include "PongPlayerController.h"
#include "PongGameMode.h"
#include "PongPlayerState.h"
#include "PongHUD.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void APongPlayerController::BeginPlay()
{
    Super::BeginPlay();

    AddOverlay();
}

void APongPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DelayInit();
}

void APongPlayerController::DelayInit()
{
    if (bDelayTransform)
    {
        if (GetPawn())
        {
            GetPawn()->SetActorTransform(DelayTransform);
            bDelayTransform = false;
        }
    }

    if (bDelayWaitStartMusic)
    {
        if (WaitStart && GetPawn() && GetPawn()->GetRootComponent() && !WaitStartComponent)
        {
            WaitStartComponent = UGameplayStatics::SpawnSoundAttached(WaitStart, GetPawn()->GetRootComponent());
            bDelayWaitStartMusic = false;
        }
    }

    if (bDelayGameStartMusic)
    {
        if (GameStart && GetPawn() && GetPawn()->GetRootComponent() && !GameStartComponent)
        {
            GameStartComponent = UGameplayStatics::SpawnSoundAttached(GameStart, GetPawn()->GetRootComponent());
            bDelayGameStartMusic = false;
        }
    }
}

void APongPlayerController::ShowWaitingText(bool bShow)
{
    Client_ShowWaitingText(bShow);
}

void APongPlayerController::UpdateScore(int32 RedScore, int32 BlueScore)
{
    Client_UpdateScore(RedScore, BlueScore);
}

void APongPlayerController::UpdateTransform(const FTransform& NewTransform)
{
    Client_UpdateTransform(NewTransform);
}

void APongPlayerController::Client_ShowWaitingText_Implementation(bool bShow)
{
    if (!IsLocalController()) return;

    HUD = !HUD ? Cast<APongHUD>(GetHUD()) : HUD;
    if (HUD)
    {
        HUD->ShowWaitingText(bShow);
    }
}

void APongPlayerController::Client_UpdateScore_Implementation(int32 RedScore, int32 BlueScore)
{
    if (!IsLocalController()) return;

    HUD = !HUD ? Cast<APongHUD>(GetHUD()) : HUD;
    if (HUD)
    {
        HUD->UpdateScore(RedScore, BlueScore);
    }
}

void APongPlayerController::Client_UpdateTransform_Implementation(const FTransform& NewTransform)
{
    if (!IsLocalController()) return;

    if (GetPawn())
    {
        GetPawn()->SetActorTransform(NewTransform);
    }
    else
    {
        bDelayTransform = true;
        DelayTransform = NewTransform;
    }
}

void APongPlayerController::AddOverlay()
{
    HUD = !HUD ? Cast<APongHUD>(GetHUD()) : HUD;
    if (HUD)
    {
        HUD->AddOverlay();
    }
}

void APongPlayerController::PlayMusicWaitStart()
{
    Client_PlayMusicWaitStart();
}

void APongPlayerController::PlayMusicGameStart()
{
    Client_PlayMusicGameStart();
}

void APongPlayerController::Client_PlayMusicWaitStart_Implementation()
{
    if (WaitStart && GetPawn() && GetPawn()->GetRootComponent() && !WaitStartComponent)
    {
        WaitStartComponent = UGameplayStatics::SpawnSoundAttached(WaitStart, GetPawn()->GetRootComponent());
    }
    else
    {
        bDelayWaitStartMusic = true;
    }
}

void APongPlayerController::Client_PlayMusicGameStart_Implementation()
{
    if (WaitStartComponent)
    {
        WaitStartComponent->Deactivate();
    }

    if (GameStart && GetPawn() && GetPawn()->GetRootComponent() && !GameStartComponent)
    {
        GameStartComponent = UGameplayStatics::SpawnSoundAttached(GameStart, GetPawn()->GetRootComponent());
    }
    else
    {
        bDelayGameStartMusic = true;
    }
}
