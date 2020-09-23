
#include "../../../Public/AI/NPC/NPC_PatrolPath_CPP.h"

#include "../../../Public/AI/Patrol_Path/Patrol_Path_CPP.h"

#include "Materials/MaterialInstanceDynamic.h"



ANPC_PatrolPath_CPP::ANPC_PatrolPath_CPP() :
	bIsAttacked(false)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANPC_PatrolPath_CPP::Melee_Attack_Implementation()
{
	if (ICombatInterfaceCPP* Interface = Cast<ICombatInterfaceCPP>(this))
	{
		Interface->Execute_Melee_Attack(this);

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("ANPC_PatrolPath_CPP")));
	}
}

void ANPC_PatrolPath_CPP::NCP_is_Attacked()
{
	bIsAttacked = true;
}

void ANPC_PatrolPath_CPP::BeginPlay()
{
	Super::BeginPlay();

	pDynamicMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);	  //create instance of dynamic material
	if (pDynamicMaterial)
	{
		pDynamicMaterial->SetVectorParameterValue("BodyColor", FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));	 //Params: Set which vector inside the Material Editor and what kind of color u want
		GetMesh()->SetMaterial(0, pDynamicMaterial);	//Set the material
	}

}