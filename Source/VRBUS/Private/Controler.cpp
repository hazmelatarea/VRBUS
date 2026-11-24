#include "Controler.h"
#include "Playe.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "SpeedModifierComponent.h"
#include "GameFramework/PlayerController.h"

UControler::UControler()
{
	PrimaryComponentTick.bCanEverTick = true;


	MoveXKey = FKey(TEXT("OculusTouch_Right_Thumbstick_X"));
	MoveYKey = FKey(TEXT("OculusTouch_Right_Thumbstick_Y"));
	TurnXKey = FKey(TEXT("OculusTouch_Left_Thumbstick_X"));
	InteractKey = FKey(TEXT("OculusTouch_Right_Trigger_Axis"));
}

void UControler::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlaye>(GetOwner());
	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();


	TArray<UMotionControllerComponent*> Controllers;
	GetOwner()->GetComponents(Controllers);
	for (UMotionControllerComponent* C : Controllers)
	{
		if (C->MotionSource == FName("LeftAim"))  LeftController = C;
		if (C->MotionSource == FName("RightAim")) RightController = C;
	}

	if (!Camera)          UE_LOG(LogTemp, Warning, TEXT("Camera not found"));
	if (!RightController) UE_LOG(LogTemp, Warning, TEXT("RightAim not found"));
	if (!LeftController)  UE_LOG(LogTemp, Warning, TEXT("LeftAim not found"));
}

APlayerController* UControler::GetPC() const
{
	return PlayerRef ? Cast<APlayerController>(PlayerRef->GetController()) : nullptr;
}

void UControler::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PlayerRef || !PlayerRef->IsAlive) return;

	MovePlayer(DeltaTime);
	RotateView(DeltaTime);
	CheckInteraction();

	if (APlayerController* PC = GetPC())
	{
		const bool bPressed = PC->GetInputAnalogKeyState(InteractKey) > 0.5f;
		if (bPressed && !bTriggerWasPressed) HandleInteraction();
		bTriggerWasPressed = bPressed;
	}
}

// Right Joystick 
void UControler::MovePlayer(float DeltaTime)
{
	APlayerController* PC = GetPC();
	if (!PC || !Camera) return;

	float X = PC->GetInputAnalogKeyState(MoveXKey);
	float Y = PC->GetInputAnalogKeyState(MoveYKey);
	if (FMath::Abs(X) < Deadzone) X = 0.f;
	if (FMath::Abs(Y) < Deadzone) Y = 0.f;
	if (X == 0.f && Y == 0.f) return;

	FVector Forward = Camera->GetForwardVector();
	FVector Right = Camera->GetRightVector();
	Forward.Z = 0.f; Right.Z = 0.f;
	Forward.Normalize(); Right.Normalize();

	const float Mult = PlayerRef->SpeedModifier ? PlayerRef->SpeedModifier->SpeedMultiplier : 1.f;
	FHitResult Hit;
	PlayerRef->AddActorWorldOffset(
		(Forward * Y + Right * X) * MoveSpeed * Mult * DeltaTime,
		true, &Hit);
}

//Left Joystick
void UControler::RotateView(float DeltaTime)
{
	APlayerController* PC = GetPC();
	if (!PC || !Camera) return;

	const float X = PC->GetInputAnalogKeyState(TurnXKey);
	if (FMath::Abs(X) < Deadzone) return;

	const FVector Before = Camera->GetComponentLocation();
	PlayerRef->AddActorWorldRotation(FRotator(0.f, X * TurnSpeed * DeltaTime, 0.f));
	PlayerRef->AddActorWorldOffset(Before - Camera->GetComponentLocation(), true);
}

void UControler::CheckInteraction()
{
	if (!RightController) return;

	const FVector Start = RightController->GetComponentLocation();
	const FVector End = Start + RightController->GetForwardVector() * InteractionDistance;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(PlayerRef);

	HitActor = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params)
		? Hit.GetActor() : nullptr;
}

void UControler::HandleInteraction()
{
	if (!HitActor) return;
	UE_LOG(LogTemp, Log, TEXT("Interacting with: %s"), *HitActor->GetName());
}