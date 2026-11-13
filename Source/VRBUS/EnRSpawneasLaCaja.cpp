// Fill out your copyright notice in the Description page of Project Settings.


#include "EnRSpawneasLaCaja.h"
#include "CajaObjetos.h"
#include "Engine/World.h"
// Sets default values
AEnRSpawneasLaCaja::AEnRSpawneasLaCaja()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

}

// Called when the game starts or when spawned
void AEnRSpawneasLaCaja::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnRSpawneasLaCaja::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnRSpawneasLaCaja::SpawnCaja()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Thiafsafsafsafsafs is the pre-set text"));

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	UWorld* World = GetWorld();
	ACajaObjetos* SpawnedActor = World->SpawnActor<ACajaObjetos>(ActorBlueprintToSpawn, SpawnLocation, SpawnRotation);

}