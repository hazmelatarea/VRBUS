
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CajaObjetos.h"
#include "UpgradeManager.generated.h"

UCLASS(Blueprintable)
class VRBUS_API AUpgradeManager : public AActor
{
    GENERATED_BODY()

public:

    AUpgradeManager();

    virtual void BeginPlay() override;

    // Blueprint de la caja que vamos a spawnear
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caja")
    TSubclassOf<ACajaObjetos> ActorBlueprintToSpawn;

    // Desbloqueos
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
    bool HeadsetUNL;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
    bool SandwichUNL;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
    bool DrinkUNL;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
    bool ClientVipUNL;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
    bool ClientIndigentUNL;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
    int32 valor;

    // Funciones de desbloqueo
    UFUNCTION(BlueprintCallable, Category = "Upgrades")
    void UnlockClientvip();

    UFUNCTION(BlueprintCallable, Category = "Upgrades")
    void UnlockClientIndigent();

    UFUNCTION(BlueprintCallable, Category = "Upgrades")
    void UnlockHeadset();

    UFUNCTION(BlueprintCallable, Category = "Upgrades")
    void UnlockSandwich();

    UFUNCTION(BlueprintCallable, Category = "Upgrades")
    void UnlockDrink();

    // Funciones de compra
    UFUNCTION(BlueprintCallable, Category = "Upgrades")
    int32 BuyHeadset();

    UFUNCTION(BlueprintCallable, Category = "Upgrades")
    int32 BuySandwich();

    UFUNCTION(BlueprintCallable, Category = "Upgrades")
    int32 BuyDrink();

    UFUNCTION(BlueprintCallable, Category = "Upgrades")
    int32 AddValor();

    // Crear caja
    UFUNCTION(BlueprintCallable, Category = "Caja")
    ACajaObjetos* SpawnBox(int32 value, ETipoObjeto tipo);
};
