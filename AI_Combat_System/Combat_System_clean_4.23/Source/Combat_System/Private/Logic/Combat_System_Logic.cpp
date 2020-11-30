
#include "Logic/Combat_System_Logic.h"


#include "AI/NPC/NPC_PatrolPath_CPP.h"
#include "Components/Combat_Component_CPP.h"
#include "Combat_System/Combat_SystemCharacter.h"
#include "Base_Classes/Base_Character.h"


ACombat_System_Logic::ACombat_System_Logic() :
	NPC_Array({}),
	pPlayer(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACombat_System_Logic::BeginPlay()
{
	Super::BeginPlay();
	
	//OnOverlapBeginDelegate.AddDynamic(this, &UCombat_Component_CPP::OnOverlapBegin);
}

void ACombat_System_Logic::Add_NPC(ANPC_PatrolPath_CPP* const NPC)
{
	if(!NPC->FindComponentByClass<UCombat_Component_CPP>())	
	{
		return;
	}
	
	NPC_Array.AddUnique(NPC);	//add only if UCombat_Component_CPP is attached to class
}

void ACombat_System_Logic::Remove_NPC(ANPC_PatrolPath_CPP* const NPC)
{
	NPC_Array.Remove(NPC);
}

void ACombat_System_Logic::Add_Player(ACombat_SystemCharacter* const Player)
{
	if(!Player->FindComponentByClass<UCombat_Component_CPP>())	
	{
		return;
	}

	pPlayer = Player;
}

void ACombat_System_Logic::Remove_Player()
{
	pPlayer = nullptr;
}

//void ACombat_System_Logic::Attack_NPC(ANPC_PatrolPath_CPP* const NPC, ACombat_SystemCharacter* const DamageCauser)
void ACombat_System_Logic::Attack_NPC(ABase_Character* const NPC)
{
	//for(ANPC_PatrolPath_CPP * const Single_NPC : NPC_Array)
	//{
	//	if(Single_NPC && NPC && Single_NPC == NPC) 
	//	{
	//		
	//	}
	//}
	if(ANPC_PatrolPath_CPP * NPC_PatrolPath = Cast<ANPC_PatrolPath_CPP>(NPC))
	{
		NPC->SetIsAttacked(true);
	}
}