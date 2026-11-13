
#include "CajaObjetos.h"

ACajaObjetos::ACajaObjetos()
{
}

ACajaObjetos::ACajaObjetos(int valor, ETipoObjeto Tipo)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("This is the pre-set text"));

    PrimaryActorTick.bCanEverTick = false;
	Tipo = Tipo;
    Valor = valor;
}


int ACajaObjetos::GetValor()
{
	return Valor;
}

ETipoObjeto ACajaObjetos::GetTipo()
{
	return Tipo;
}

void DestroyActor(ACajaObjetos* Actor)
{
	if (Actor)
	{
		Actor->Destroy();
	}
}



