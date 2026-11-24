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

	//Movement speed settings
	UPROPERTY(EditAnywhere, Category = "VR|Settings")
	float MoveSpeed = 200.f;

	//Camera speed rotation settings
	UPROPERTY(EditAnywhere, Category = "VR|Settings")
	float TurnSpeed = 90.f;

	//Joystick Dead Zone Settings
	UPROPERTY(EditAnywhere, Category = "VR|Settings")
	float Deadzone = 0.2f;

	//Interaction distance settings
	UPROPERTY(EditAnywhere, Category = "VR|Settings")
	float InteractionDistance = 300.f;

	//Jump force settings
	UPROPERTY(EditAnywhere, Category = "VR|Settings")
	float JumpForce = 400.f;

	//Gravity settings for the jump
	UPROPERTY(EditAnywhere, Category = "VR|Settings")
	float Gravity = 980.f;

	// Keys 
	UPROPERTY(EditAnywhere, Category = "VR|Keys")
	FKey MoveXKey;

	UPROPERTY(EditAnywhere, Category = "VR|Keys")
	FKey MoveYKey;

	UPROPERTY(EditAnywhere, Category = "VR|Keys")
	FKey TurnXKey;

	UPROPERTY(EditAnywhere, Category = "VR|Keys")
	FKey InteractKey;

	UPROPERTY(EditAnywhere, Category = "VR|Keys")
	FKey JumpKey;

	void MovePlayer(float DeltaTime);
	void RotateView(float DeltaTime);
	void CheckInteraction();
	void HandleInteraction();

	UFUNCTION(BlueprintCallable, Category = "VR")
	void Jump();
	void UpdateJump(float DeltaTime);

private:
	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY()
	AActor* HitActor = nullptr;

	bool bTriggerWasPressed = false;

	bool bIsJumping = false;
	bool bJumpWasPressed = false;
	float VerticalVelocity = 0.f;
	float GroundZ = 0.f;

	APlayerController* GetPC() const;
};