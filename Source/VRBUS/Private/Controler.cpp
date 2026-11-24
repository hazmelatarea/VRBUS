#include "Controler.h"
#include "Playe.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "SpeedModifierComponent.h"
#include "GameFramework/PlayerController.h"

UControler::UControler()
{
	//Update every frame
	PrimaryComponentTick.bCanEverTick = true;

	//Right Joystick for horizontal movement
	MoveXKey = FKey(TEXT("OculusTouch_Right_Thumbstick_X"));

	//Right Joystick for vertical movement
	MoveYKey = FKey(TEXT("OculusTouch_Right_Thumbstick_Y"));

	//Left Joystick for horizontal rotation
	TurnXKey = FKey(TEXT("OculusTouch_Left_Thumbstick_X"));

	//Right Trrigger for interaction
	InteractKey = FKey(TEXT("OculusTouch_Right_Trigger_Axis"));

	//Right Joystick button for jump
	JumpKey = FKey(TEXT("OculusTouch_Right_Thumbstick"));
}

void UControler::BeginPlay()
{
	Super::BeginPlay();

	//Get the player reference and camera component
	PlayerRef = Cast<APlaye>(GetOwner());
	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();

	//Get the motion controller components
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

//Get the player controller from the player reference
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

		const bool bJumpPressed = PC->IsInputKeyDown(JumpKey);
		if (bJumpPressed && !bJumpWasPressed) Jump();
		bJumpWasPressed = bJumpPressed;
	}

	UpdateJump(DeltaTime);
}

// Right Joystick 
void UControler::MovePlayer(float DeltaTime)
{
	APlayerController* PC = GetPC();
	if (!PC || !Camera) return;

	//Horizontal an vertical values from right joystick
	float X = PC->GetInputAnalogKeyState(MoveXKey);
	float Y = PC->GetInputAnalogKeyState(MoveYKey);

	//Ignore small values to avoid drift
	if (FMath::Abs(X) < Deadzone) X = 0.f;
	if (FMath::Abs(Y) < Deadzone) Y = 0.f;
	if (X == 0.f && Y == 0.f) return;

	//Get the forward and right vectors of the camera
	FVector Forward = Camera->GetForwardVector();
	FVector Right = Camera->GetRightVector();
	Forward.Z = 0.f; Right.Z = 0.f;
	Forward.Normalize(); Right.Normalize();

	//SpeedModifier component to modify the movement speed
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

//Check interaction 
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

//Handle interaction with the hit actor 
void UControler::HandleInteraction()
{
	if (!HitActor) return;
	UE_LOG(LogTemp, Log, TEXT("Interacting with: %s"), *HitActor->GetName());
}

//Initiate jump
void UControler::Jump()
{
	if (!PlayerRef || bIsJumping) return;

	bIsJumping = true;
	GroundZ = PlayerRef->GetActorLocation().Z;
	VerticalVelocity = JumpForce;
}

//Jump movement upadte and check for landing
void UControler::UpdateJump(float DeltaTime)
{
	if (!PlayerRef || !bIsJumping) return;

	VerticalVelocity -= Gravity * DeltaTime;

	FHitResult Hit;
	PlayerRef->AddActorWorldOffset(FVector(0.f, 0.f, VerticalVelocity * DeltaTime), true, &Hit);

	if (Hit.bBlockingHit && VerticalVelocity > 0.f)
	{
		VerticalVelocity = 0.f;
	}

	const FVector Location = PlayerRef->GetActorLocation();
	if (Hit.bBlockingHit || Location.Z <= GroundZ)
	{
		PlayerRef->SetActorLocation(FVector(Location.X, Location.Y, FMath::Max(Location.Z, GroundZ)));
		bIsJumping = false;
		VerticalVelocity = 0.f;
	}
}