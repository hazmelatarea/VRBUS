#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Playe.generated.h"

class UControler;
class USpeedModifierComponent;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);

UCLASS()
class VRBUS_API APlaye : public APawn
{
	GENERATED_BODY()

public:
	APlaye();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speed")
	USpeedModifierComponent* SpeedModifier;

	// Player money
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Money = 0.f;

	// Player Alive status
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	bool IsAlive = true;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnPlayerDied OnDied;

	// Controller component for VR input and movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	UControler* VRController;

	//Add money
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AddMoney(float Amount);

	//Spend money
	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool SpendMoney(float Amount);

	//Checks if the player can afford the amount
	UFUNCTION(BlueprintPure, Category = "Stats")
	bool CanAfford(float Amount) const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Die();
};