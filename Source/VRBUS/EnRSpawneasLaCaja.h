// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnRSpawneasLaCaja.generated.h"

UCLASS()
class VRBUS_API AEnRSpawneasLaCaja : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnRSpawneasLaCaja();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnCaja();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Valor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	TSubclassOf<AActor> ActorBlueprintToSpawn;
};
