#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Caja.generated.h"

UCLASS()
class VRBUS_API ACaja : public AActor
{
    GENERATED_BODY()

public:

    ACaja();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Caja")
    int32 Cantidad = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Caja")
    FName TipoObjeto;

public:

    // Inicializar la caja
    UFUNCTION(BlueprintCallable, Category = "Caja")
    void InicializarCaja(FName NuevoTipo, int32 NuevaCantidad);

    // Consultar cantidad
    UFUNCTION(BlueprintCallable, Category = "Caja")
    int32 ObtenerCantidad() const;

    // Consultar tipo
    UFUNCTION(BlueprintCallable, Category = "Caja")
    FName ObtenerTipo() const;
};