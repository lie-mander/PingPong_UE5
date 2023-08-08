#pragma once

UENUM(BlueprintType)
enum class EPongTeam : uint8
{
    EPT_RedTeam UMETA(DisplayName = "RedTeam"),
    EPT_BlueTeam UMETA(DisplayName = "BlueTeam"),

    EPT_MAX UMETA(DisplayName = "MAX")
};
