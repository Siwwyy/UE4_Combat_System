#include "../Public/NPC_SpawnerCPP.h"

#include "Math/UnrealMathUtility.h"
#include "Math/TransformNonVectorized.h"

#include "../Public/AI/NPC/NPC_PatrolPath_CPP.h"

ANPC_SpawnerCPP::ANPC_SpawnerCPP() :
	pStatic_Mesh(CreateDefaultSubobject<UStaticMeshComponent>("UStaticMeshComponent")),
	pPatrol_Path(nullptr),
	pNPC(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANPC_SpawnerCPP::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Spawned a new NPC")));
	Spawn_NPC();
}

void ANPC_SpawnerCPP::Spawn_NPC()
{
	UWorld* world = GetWorld();
	if (pNPC && world)
	{
		FRotator SpawnRotation{ RootComponent->GetComponentRotation()};
		FVector SpawnLocation{ RootComponent->GetComponentLocation() };
		const FTransform SpawnLocAndRotation(SpawnRotation, SpawnLocation);

		ANPC_PatrolPath_CPP* NPC = world->SpawnActorDeferred<ANPC_PatrolPath_CPP>(pNPC, SpawnLocAndRotation);
		if (NPC)
		{
			NPC->Set_pPatrol_Path(pPatrol_Path);
			NPC->FinishSpawning(SpawnLocAndRotation);
		}
	}
}

void ANPC_SpawnerCPP::Delete_NPC()
{

}

void ANPC_SpawnerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//int32 temp = FMath::RandRange(0, 200);
	//if (temp == 50)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Spawned a new NPC")));
	//	Spawn_NPC();
	//}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Spawned a new NPC")));
	//Spawn_NPC();
}