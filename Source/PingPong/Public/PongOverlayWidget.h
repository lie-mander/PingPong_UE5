// PingPong by Liemander

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PongOverlayWidget.generated.h"

class UTextBlock;

UCLASS()
class PINGPONG_API UPongOverlayWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* WaitingText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* RedScoreText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* BlueScoreText;
};
