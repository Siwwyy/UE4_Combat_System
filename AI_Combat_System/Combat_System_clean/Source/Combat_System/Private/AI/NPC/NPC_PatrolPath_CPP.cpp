
#include "../../../Public/AI/NPC/NPC_PatrolPath_CPP.h"


#include "DrawDebugHelpers.h"
#include "../../../Public/AI/Patrol_Path/Patrol_Path_CPP.h"
#include "../../../Public/AI/Controllers/AI_Controller.h"
#include "Combat_System/Combat_SystemCharacter.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "Components/SphereComponent.h"
#include "Components/Combat_Component_CPP.h"
#include "Perception/AISense_Damage.h"


ANPC_PatrolPath_CPP::ANPC_PatrolPath_CPP() :
	ABase_Character(),
	pPatrol_Path(nullptr),
	pAi_Controller(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	//Member Variables Initialization
	fDamage = 1.f;
	CharacterType = Character_Type::Neutral;
	//////////////////////////////////////
	

	pCombat_Component_CPP->Get_pSphereComponent()->SetupAttachment(GetMesh(), FName("s_hand_punch"));
}

void ANPC_PatrolPath_CPP::BeginPlay()
{
	Super::BeginPlay();

	if (pDynamicMaterial)
	{
		pDynamicMaterial->SetVectorParameterValue("BodyColor", FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));	 //Params: Set which vector inside the Material Editor and what kind of color u want
		GetMesh()->SetMaterial(0, pDynamicMaterial);	//Set the material
	}

}

float ANPC_PatrolPath_CPP::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	UAISense_Damage::ReportDamageEvent(GetWorld(), this, DamageCauser, ActualDamage, GetActorLocation(), FVector(ForceInit));
	
	return ActualDamage;
}

void ANPC_PatrolPath_CPP::Set_pPatrol_Path(APatrol_Path_CPP* const ptr)
{
	if (!ptr)
	{
		return;
	}
	pPatrol_Path = ptr;
}

void ANPC_PatrolPath_CPP::Set_pAi_Controller(AAI_Controller* const ptr)
{
	if (!ptr)
	{
		return;
	}
	pAi_Controller = ptr;
}