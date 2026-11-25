// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_Upgrade.generated.h"

//UENUM(BlueprintType)
//enum class EAttributeType : uint8
//{
//	Velocity    UMETA(DisplayName = "Velocity"),
//	Seats       UMETA(DisplayName = "Seats"),
//	Tickets     UMETA(DisplayName = "TicketsVip")
//};

UCLASS()
class VRBUS_API UPDA_Upgrade : public UPrimaryDataAsset
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
		int price;

		//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
		//float ModifierValue;
		//No me queda muy claro si diferencianlo en categorias 

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
		float ModifierValue;
	
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
		TObjectPtr<UTexture2D> Icon;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
		TObjectPtr<UStaticMesh> Mesh;
};

//para array TArray<TObjectPtr<UPDA_Upgrade>> Upgrades;
