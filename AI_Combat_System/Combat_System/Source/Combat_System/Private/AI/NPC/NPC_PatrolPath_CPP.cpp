
#include "../../../Public/AI/NPC/NPC_PatrolPath_CPP.h"

#include "../../../Public/AI/Patrol_Path/Patrol_Path_CPP.h"
#include "../../../Public/AI/Controllers/AI_Controller.h"
#include "Combat_System/Combat_SystemCharacter.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "Components/BoxComponent.h"


ANPC_PatrolPath_CPP::ANPC_PatrolPath_CPP() :
	pDynamicMaterial(nullptr),
	pPatrol_Path(nullptr),
	pAi_Controller(nullptr),
	bIsAttacked(false)
{
	PrimaryActorTick.bCanEverTick = false;

	pBox_Component = CreateDefaultSubobject<UBoxComponent>(TEXT("pBox_Component"));
	pBox_Component->SetupAttachment(GetMesh(), FName("s_hand_punch"));

}

float ANPC_PatrolPath_CPP::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//custom logic in here
	if (ACombat_SystemCharacter* Player = Cast<ACombat_SystemCharacter>(DamageCauser))
	{
		bIsAttacked = true;
		pAttacking_Player = Player;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Take damage NPC: %s"), *DamageCauser->GetName()));
	}

	return ActualDamage;
}

void ANPC_PatrolPath_CPP::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACombat_SystemCharacter* Player = Cast<ACombat_SystemCharacter>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("OnOverlapBegin from NPC: %s"), *OtherActor->GetName()));
		Player->TakeDamage(50.f, FDamageEvent(), nullptr, this);
		pBox_Component->SetGenerateOverlapEvents(false);	//when I hit NPC it prevents me from i.e hitting multiple times
	}
}

void ANPC_PatrolPath_CPP::Melee_Attack_Implementation()
{
	if (ICombatInterfaceCPP* Interface = Cast<ICombatInterfaceCPP>(this))
	{
		Interface->Execute_Melee_Attack(this);

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("ANPC_PatrolPath_CPP")));
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

	pBox_Component->OnComponentBeginOverlap.AddDynamic(this, &ANPC_PatrolPath_CPP::OnOverlapBegin);
}