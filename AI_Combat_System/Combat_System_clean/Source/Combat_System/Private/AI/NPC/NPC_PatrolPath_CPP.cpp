
#include "../../../Public/AI/NPC/NPC_PatrolPath_CPP.h"


#include "DrawDebugHelpers.h"
#include "../../../Public/AI/Patrol_Path/Patrol_Path_CPP.h"
#include "../../../Public/AI/Controllers/AI_Controller.h"
#include "Combat_System/Combat_SystemCharacter.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "Kismet/GameplayStatics.h"

#include "Components/BoxComponent.h"
#include "Components/Combat_Component_CPP.h"
#include "Perception/AISense_Damage.h"


ANPC_PatrolPath_CPP::ANPC_PatrolPath_CPP() :
	ABase_Character(),
	pDynamicMaterial(nullptr),
	pPatrol_Path(nullptr),
	pAi_Controller(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	//pBox_Component = CreateDefaultSubobject<UBoxComponent>(TEXT("pBox_Component"));
	//pBox_Component->SetupAttachment(GetMesh(), FName("s_hand_punch"));

	fDamage = 5.f;
	
	pCombat_Component_CPP = CreateDefaultSubobject<UCombat_Component_CPP>(TEXT("pCombat_Component_CPP"));
	pCombat_Component_CPP->Get_pBoxComponent()->SetupAttachment(GetMesh(), FName("s_hand_punch"));
}

float ANPC_PatrolPath_CPP::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//custom logic in here


	bIsAttacked = true;
	fHealth -= DamageAmount;
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("ANPC_PatrolPath_CPP health: %f"), fHealth));
	DrawDebugString(GetWorld(), DamageCauser->GetActorLocation(), FString::Printf(TEXT("ANPC_PatrolPath_CPP health: %f"), fHealth), 0, FColor::Green,0.4f,false,3.f);

	if (fHealth <= 0.f)
	{
		Destroy();
	}

	UAISense_Damage::ReportDamageEvent(GetWorld(), this, DamageCauser, DamageAmount, GetActorLocation(), FVector(ForceInit));
	

	return DamageAmount;
}

void ANPC_PatrolPath_CPP::Melee_Attack_Implementation()
{
	if (ICombatInterfaceCPP* Interface = Cast<ICombatInterfaceCPP>(this))
	{
		Interface->Execute_Melee_Attack(this);
	}
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

void ANPC_PatrolPath_CPP::BeginPlay()
{
	Super::BeginPlay();

	pDynamicMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);	  //create instance of dynamic material
	if (pDynamicMaterial)
	{
		pDynamicMaterial->SetVectorParameterValue("BodyColor", FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));	 //Params: Set which vector inside the Material Editor and what kind of color u want
		GetMesh()->SetMaterial(0, pDynamicMaterial);	//Set the material
	}

	//pBox_Component->OnComponentBeginOverlap.AddDynamic(this, &ANPC_PatrolPath_CPP::OnOverlapBegin);
}