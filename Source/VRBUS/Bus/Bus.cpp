// Fill out your copyright notice in the Description page of Project Settings.


#include "Bus/Bus.h"

// Sets default values
ABus::ABus()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABus::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABus::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

