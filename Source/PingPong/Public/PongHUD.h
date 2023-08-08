// PingPong by Liemander

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PongHUD.generated.h"

class UPongOverlayWidget;

UCLASS()
class PINGPONG_API APongHUD : public AHUD
{
    GENERATED_BODY()

public:
    void AddOverlay();
    void ShowWaitingText(bool bShow);
    void UpdateScore(int32 RedScore, int32 BlueScore);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Pong | Widgets")
    TSubclassOf<UUserWidget> PongOverlayWidgetClass;

    UPROPERTY()
    UPongOverlayWidget* PongOverlayWidget;
};
