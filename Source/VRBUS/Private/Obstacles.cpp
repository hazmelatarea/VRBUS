#include "Obstacles.h"
#include "Playe.h"
#include "SpeedModifierComponent.h"
#include "Components/BoxComponent.h"

FOnDayRestartRequested AObstacles::OnDayRestartRequested;

AObstacles::AObstacles()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Trigger->SetGenerateOverlapEvents(true);
	RootComponent = Trigger;

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AObstacles::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AObstacles::OnEndOverlap);
}

void AObstacles::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ApplyEffect(OtherActor);
}

void AObstacles::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Al salir de un obstáculo lento, la velocidad vuelve a la normal
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

	if (ObstacleType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Obstacle.Deadly"), false)))
	{
		KillPlayer(Other);
	}
	else if (ObstacleType.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Obstacle.Slow"), false)))
	{
		SlowDownBus(Other);
	}
}

void AObstacles::SlowDownBus(AActor* Other)
{
	if (!Other) return;

	if (USpeedModifierComponent* Speed = Other->FindComponentByClass<USpeedModifierComponent>())
	{
		Speed->SpeedMultiplier = VelocityReduction;
	}
}

void AObstacles::KillPlayer(AActor* Other)
{
	if (!Other) return;

	// Si es el jugador, también muere (lanza su evento OnDied)
	if (APlaye* Player = Cast<APlaye>(Other))
	{
		Player->Die();
	}

	// Avisa al Game Manager para que haga RestartDay()
	OnDayRestartRequested.Broadcast(Other);
}