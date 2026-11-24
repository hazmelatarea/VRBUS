#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpeedModifierComponent.generated.h"

UCLASS(ClassGroup = (VR), meta = (BlueprintSpawnableComponent))
class VRBUS_API USpeedModifierComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USpeedModifierComponent();

	// 1 = normal speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float SpeedMultiplier = 1.f;
};