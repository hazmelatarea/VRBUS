
#include "UpgradeManager.h"
#include "Engine/World.h"

AUpgradeManager::AUpgradeManager()
{
    PrimaryActorTick.bCanEverTick = false;

    HeadsetUNL = false;
    SandwichUNL = false;
    DrinkUNL = false;
    ClientVipUNL = false;
    ClientIndigentUNL = false;

    valor = 0;
}

void AUpgradeManager::BeginPlay()
{
    Super::BeginPlay();
}

void AUpgradeManager::UnlockClientvip()
{
    ClientVipUNL = true;
}

void AUpgradeManager::UnlockClientIndigent()
{
    ClientIndigentUNL = true;
}

void AUpgradeManager::UnlockHeadset()
{
    HeadsetUNL = true;
}

void AUpgradeManager::UnlockSandwich()
{
    SandwichUNL = true;
}

void AUpgradeManager::UnlockDrink()
{
    DrinkUNL = true;
}

int32 AUpgradeManager::BuyHeadset()
{
    return 0;
}

int32 AUpgradeManager::BuySandwich()
{
    return 1;
}

int32 AUpgradeManager::BuyDrink()
{
    return 2;
}

int32 AUpgradeManager::AddValor()
{
    return valor++;
}

ACajaObjetos* AUpgradeManager::SpawnBox(int32 value, ETipoObjeto tipo)
{
    // Comprobar que tenemos asignado el Blueprint
    if (!ActorBlueprintToSpawn)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("No se ha asignado BP_BOX en UpgradeManager"));

        return nullptr;
    }

    // Comprobar que existe el mundo
    UWorld* World = GetWorld();

    if (!World)
    {
        UE_LOG(LogTemp, Error,
            TEXT("No se ha podido obtener el World"));

        return nullptr;
    }

    // Posicion y rotacion de spawn
    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();

    // Configuracion del spawn
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // Crear el actor BOX
    ACajaObjetos* SpawnedActor = World->SpawnActor<ACajaObjetos>(
        ActorBlueprintToSpawn,
        SpawnLocation,
        SpawnRotation,
        SpawnParams
    );

    // Comprobar que se ha creado correctamente
    if (SpawnedActor)
    {
        SpawnedActor->Valor = value;
        SpawnedActor->Tipo = tipo;

        UE_LOG(LogTemp, Warning,
            TEXT("Caja creada. Valor: %d, Tipo: %d"),
            value,
            (int32)tipo);
    }
    else
    {
        UE_LOG(LogTemp, Error,
            TEXT("No se ha podido crear la caja"));
    }

    return SpawnedActor;
}
