// Fill out your copyright notice in the Description page of Project Settings.


#include "Caja.h"

// Sets default values
ACaja::ACaja()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACaja::InicializarCaja(FName NuevoTipo, int32 NuevaCantidad)
{
}

int32 ACaja::ObtenerCantidad() const
{
	return int32();
}

FName ACaja::ObtenerTipo() const
{
	return FName();
}

