#include "../Public/Actors/NPC_SpawnerCPP.h"


#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

#include "../Public/AI/NPC/NPC_PatrolPath_CPP.h"
#include "Logic/Combat_System_Logic.h"

ANPC_SpawnerCPP::ANPC_SpawnerCPP() :
	pStatic_Mesh(CreateDefaultSubobject<UStaticMeshComponent>("UStaticMeshComponent")),
	SpawnTimerHandle({}),
	pPatrol_Path(nullptr),
	pNPC(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANPC_SpawnerCPP::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ANPC_SpawnerCPP::Spawn, 5.f, true, 2.f);	//for tests purposes, 50.f is a delay between spawning
}

void ANPC_SpawnerCPP::Spawn() const
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Spawned a new NPC")));
	static int a = 0;

	if(a <= 2)
	{
			Spawn_NPC();
	}
	++a;

}

void ANPC_SpawnerCPP::Spawn_NPC() const
{
	UWorld* world = GetWorld();
	if (pNPC && world)
	{
		const FRotator SpawnRotation{ RootComponent->GetComponentRotation() };
		const FVector SpawnLocation{ RootComponent->GetComponentLocation() };
		const FTransform SpawnLocAndRotation(SpawnRotation, SpawnLocation);

		ANPC_PatrolPath_CPP* NPC = world->SpawnActorDeferred<ANPC_PatrolPath_CPP>(pNPC, SpawnLocAndRotation);
		if (NPC)
		{
			//NPC->SetCharacter_Type(Character_Type::Aggressor);
			NPC->Set_pPatrol_Path(pPatrol_Path);
			pCombat_System_Logic->Add_NPC(NPC);
			NPC->FinishSpawning(SpawnLocAndRotation);
		}
	}
}