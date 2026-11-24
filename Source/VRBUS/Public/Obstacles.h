#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Obstacles.generated.h"

class UBoxComponent;

// Aviso para el Game Manager (solo C++): alguien tocó un obstáculo mortal
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDayRestartRequested, AActor* /*Culpable*/);

UCLASS()
class VRBUS_API AObstacles : public AActor
{
	GENERATED_BODY()

public:
	AObstacles();

	// Obstacle.Slow = ralentiza, Obstacle.Deadly = reinicia el día
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	FGameplayTag ObstacleType;

	// Multiplicador de velocidad (0.5 = mitad). Solo se usa con Obstacle.Slow
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VelocityReduction = 0.5f;

	// El Game Manager se enlaza a esto: AObstacle::OnDayRestartRequested.AddUObject(...)
	static FOnDayRestartRequested OnDayRestartRequested;

	UFUNCTION(BlueprintCallable, Category = "Obstacles")
	void ApplyEffect(AActor* Other);

	UFUNCTION(BlueprintCallable, Category = "Obstacles")
	void SlowDownBus(AActor* Other);

	UFUNCTION(BlueprintCallable, Category = "Obstacles")
	void KillPlayer(AActor* Other);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacles")
	UBoxComponent* Trigger;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};