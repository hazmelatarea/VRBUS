// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CajaObjeto.generated.h"

UCLASS()
class VRBUS_API ACajaObjeto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACajaObjeto();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
