
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
    int32 Valor;
};

UCLASS(Blueprintable)
class VRBUS_API ACajaObjetos : public AActor
{
    GENERATED_BODY()

public:
    ACajaObjetos();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caja")
    int32 Valor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caja")
    ETipoObjeto Tipo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caja")
    TArray<FObjetoInventario> Inventario;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Caja")
    int32 GetValor() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Caja")
    ETipoObjeto GetTipo() const;
    UFUNCTION(BlueprintCallable, Category = "Caja")
    void SpawnObject();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objetos")
    TSubclassOf<AActor> CascoBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objetos")
    TSubclassOf<AActor> BebidaBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objetos")
    TSubclassOf<AActor> SandwichBlueprint;

};
