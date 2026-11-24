#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputCoreTypes.h"
#include "Controler.generated.h"

class APlaye;
class UCameraComponent;
class UMotionControllerComponent;
class APlayerController;

UCLASS(ClassGroup = (VR), meta = (BlueprintSpawnableComponent))
class VRBUS_API UControler : public UActorComponent
{
	GENERATED_BODY()

public:
	UControler();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = "VR")
	APlaye* PlayerRef;

	UPROPERTY(BlueprintReadOnly, Category = "VR")
	UMotionControllerComponent* LeftController;

	UPROPERTY(BlueprintReadOnly, Category = "VR")
	UMotionControllerComponent* RightController;

	UPROPERTY(EditAnywhere, Category = "VR|Ajustes")
	float MoveSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "VR|Ajustes")
	float TurnSpeed = 90.f;

	UPROPERTY(EditAnywhere, Category = "VR|Ajustes")
	float Deadzone = 0.2f;

	UPROPERTY(EditAnywhere, Category = "VR|Ajustes")
	float InteractionDistance = 300.f;

	// Keys 
	UPROPERTY(EditAnywhere, Category = "VR|Teclas")
	FKey MoveXKey;

	UPROPERTY(EditAnywhere, Category = "VR|Teclas")
	FKey MoveYKey;

	UPROPERTY(EditAnywhere, Category = "VR|Teclas")
	FKey TurnXKey;

	UPROPERTY(EditAnywhere, Category = "VR|Teclas")
	FKey InteractKey;

	void MovePlayer(float DeltaTime);
	void RotateView(float DeltaTime);
	void CheckInteraction();
	void HandleInteraction();

private:
	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY()
	AActor* HitActor = nullptr;

	bool bTriggerWasPressed = false;

	APlayerController* GetPC() const;
};