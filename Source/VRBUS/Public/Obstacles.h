#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Obstacles.generated.h"

class UBoxComponent;

//Mortal Obstacle touch
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDayRestartRequested, AActor*);

UCLASS()
class VRBUS_API AObstacles : public AActor
{
	GENERATED_BODY()

public:
	AObstacles();

	// Obstacle.Slow, Obstacle.Deadly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	FGameplayTag ObstacleType;

	//Spped reduction multiplier, 0.0= no movement, 1.0= no effect just for the slow type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VelocityReduction = 0.5f;

	//Restart the day when the player dies
	static FOnDayRestartRequested OnDayRestartRequested;

	//Apply the effect of the obstacle to the player 
	UFUNCTION(BlueprintCallable, Category = "Obstacles")
	void ApplyEffect(AActor* Other);

	//Slow down
	UFUNCTION(BlueprintCallable, Category = "Obstacles")
	void SlowDownBus(AActor* Other);

	//Mortal Effect
	UFUNCTION(BlueprintCallable, Category = "Obstacles")
	void KillPlayer(AActor* Other);

protected:

	//Collision component to detect overlaps
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacles")
	UBoxComponent* Trigger;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Collision end overlap
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};