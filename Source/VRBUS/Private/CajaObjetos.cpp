
#include "CajaObjetos.h"

ACajaObjetos::ACajaObjetos()
{
    PrimaryActorTick.bCanEverTick = false;

    Valor = 0;
    Tipo = ETipoObjeto::Casco;
}

int32 ACajaObjetos::GetValor() const
{
    return Valor;
}

ETipoObjeto ACajaObjetos::GetTipo() const
{
    return Tipo;
}

void ACajaObjetos::SpawnObject()
{

    TSubclassOf<AActor> Objeto;

    switch (Tipo)
    {
    case ETipoObjeto::Casco:
        Objeto = CascoBlueprint;
        break;

    case ETipoObjeto::Bebida:
        Objeto = BebidaBlueprint;
        break;

    case ETipoObjeto::Sandwich:
        Objeto = SandwichBlueprint;
        break;
    }

    if (!Objeto)
    {
        UE_LOG(LogTemp, Warning, TEXT("No se ha asignado el Blueprint del objeto"));
        return;
    }

    FVector Location = GetActorLocation() + FVector(0, 0, 100);
    FRotator Rotation = GetActorRotation();

    GetWorld()->SpawnActor<AActor>(
        Objeto,
        Location,
        Rotation
    );

    Valor--;

    if (Valor <= 0)
    {
        Destroy();
    }
}
