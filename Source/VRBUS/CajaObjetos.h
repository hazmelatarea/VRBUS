
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CajaObjetos.generated.h"

UENUM(BlueprintType)
enum class ETipoObjeto : uint8
{
    Casco,
    Bebida,
    Sandwich
};

USTRUCT(BlueprintType)
struct FObjetoInventario
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETipoObjeto Tipo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Valor;
};

UCLASS()
class VRBUS_API ACajaObjetos : public AActor
{
    GENERATED_BODY()

public:
    ACajaObjetos();
    ACajaObjetos(int valor, ETipoObjeto Tipo);

    int GetValor();
    ETipoObjeto GetTipo();
    TArray<FObjetoInventario> Inventario;

    // Valor entero que recibirá la caja al crearse
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Valor;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETipoObjeto Tipo;

    void SpawnObject();
};
