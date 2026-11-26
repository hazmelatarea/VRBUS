#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_Consumible.generated.h"

UENUM(BlueprintType)
enum class ObjectType : uint8
{
	Casco,
	Bebida,
	Sandwich
};

UCLASS()
class VRBUS_API UPDA_Consumible : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ObjectType TipoObjeto;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icono;
};
