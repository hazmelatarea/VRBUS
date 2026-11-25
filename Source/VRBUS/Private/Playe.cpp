#include "Playe.h"
#include "Controler.h"
#include "SpeedModifierComponent.h"
#include "Components/SphereComponent.h"

APlaye::APlaye()
{
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(40.f);
	Collision->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = Collision;

	VRController = CreateDefaultSubobject<UControler>(TEXT("VRController"));
	SpeedModifier = CreateDefaultSubobject<USpeedModifierComponent>(TEXT("SpeedModifier"));
}

void APlaye::AddMoney(float Amount)
{
	if (!IsAlive || Amount <= 0.f) return;
	Money += Amount;
}

bool APlaye::SpendMoney(float Amount)
{
	if (!IsAlive || Amount <= 0.f || !CanAfford(Amount)) return false;
	Money -= Amount;
	return true;
}

bool APlaye::CanAfford(float Amount) const
{
	return Money >= Amount;
}

void APlaye::Die()
{
	if (!IsAlive) return;
	IsAlive = false;
	OnDied.Broadcast();
}