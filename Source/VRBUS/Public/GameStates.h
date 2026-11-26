#pragma once

#include "CoreMinimal.h"
#include "GameStates.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
    Start      UMETA(DisplayName = "Start"),
    Preparation      UMETA(DisplayName = "Preparation"),
    Drive       UMETA(DisplayName = "Drive"),
    BusStop    UMETA(DisplayName = "BusStop"),
    Sleep   UMETA(DisplayName = "Sleep")
};