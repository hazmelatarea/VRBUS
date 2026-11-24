#include "Obstacles.h"
#include "Playe.h"
#include "SpeedModifierComponent.h"
#include "Components/BoxComponent.h"

//Use to restar the day when the player dies
FOnDayRestartRequested AObstacles::OnDayRestartRequested;

AObstacles::AObstacles()
{
	PrimaryActorTick.bCanEverTick = false;

	//Colision component to detect overlaps
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Trigger->SetGenerateOverlapEvents(true);
	RootComponent = Trigger;

	//In or out of the collision
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AObstacles::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AObstacles::OnEndOverlap);
}

//Detect when something enters the collision
void AObstacles::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ApplyEffect(OtherActor);
}

//Detect when something leaves the collision
void AObstacles::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	if (!OtherActor) return;
	if (!ObstacleType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Obstacle.Slow"), false))) return;

	if (USpeedModifierComponent* Speed = OtherActor->FindComponentByClass<USpeedModifierComponent>())
	{
		Speed->SpeedMultiplier = 1.f;
	}
}

void AObstacles::ApplyEffect(AActor* Other)
{
	if (!Other) return;

	//Check the type of obstacle and apply effect
	if (ObstacleType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Obstacle.Deadly"), false)))
	{
		KillPlayer(Other);
	}
	else if (ObstacleType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Obstacle.Slow"), false)))
	{
		SlowDownBus(Other);
	}
}

//Slow down speed
void AObstacles::SlowDownBus(AActor* Other)
{
	if (!Other) return;

	if (USpeedModifierComponent* Speed = Other->FindComponentByClass<USpeedModifierComponent>())
	{
		Speed->SpeedMultiplier = VelocityReduction;
	}
}

//Kill the player and restart the day
void AObstacles::KillPlayer(AActor* Other)
{
	if (!Other) return;


	if (APlaye* Player = Cast<APlaye>(Other))
	{
		Player->Die();
	}

	// Game Manager listen to the event 
	OnDayRestartRequested.Broadcast(Other);
}