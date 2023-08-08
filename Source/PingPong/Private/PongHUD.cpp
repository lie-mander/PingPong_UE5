// PingPong by Liemander

#include "PongHUD.h"
#include "PongOverlayWidget.h"
#include "GameFramework/PlayerController.h"
#include "Components/TextBlock.h"

void APongHUD::AddOverlay()
{
    APlayerController* OwnerController = GetOwningPlayerController();
    if (OwnerController && PongOverlayWidgetClass && !PongOverlayWidget)
    {
        PongOverlayWidget = CreateWidget<UPongOverlayWidget>(OwnerController, PongOverlayWidgetClass);
        PongOverlayWidget->AddToViewport();
    }
}

void APongHUD::ShowWaitingText(bool bShow)
{
    if (!PongOverlayWidget)
    {
        AddOverlay();
    }

    if (PongOverlayWidget)
    {
        const ESlateVisibility Visibility = bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
        PongOverlayWidget->WaitingText->SetVisibility(Visibility);
    }
}

void APongHUD::UpdateScore(int32 RedScore, int32 BlueScore) 
{
    if (!PongOverlayWidget)
    {
        AddOverlay();
    }

    if (PongOverlayWidget)
    {
        PongOverlayWidget->RedScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d"), RedScore)));
        PongOverlayWidget->BlueScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d"), BlueScore)));
    }
}
