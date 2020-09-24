#include "../Public/NPC_SpawnerCPP.h"

#include "Math/UnrealMathUtility.h"


#include "../Public/AI/NPC/Spawnable_NPC_CPP.h"
#include "../Public/AI/NPC/NPC_PatrolPath_CPP.h"
#include "../Public/AI/Controllers/AI_Controller.h"

ANPC_SpawnerCPP::ANPC_SpawnerCPP() :
	pStatic_Mesh(CreateDefaultSubobject<UStaticMeshComponent>("UStaticMeshComponent")),
	pPatrol_Path(nullptr),
	pAi_Controller(nullptr),
	pNPC(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANPC_SpawnerCPP::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Spawned a new NPC")));
	Add_NPC();
}

void ANPC_SpawnerCPP::Add_NPC()
{
	UWorld* world = GetWorld();
	if (pNPC && world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		//FRotator SpawnRotation(0.f,0.f,90.f);
		FRotator SpawnRotation(0.f, 0.f, 0.f);
		//FVector SpawnLocation(-1880.f, -3080.f, 218.f);
		FVector SpawnLocation = RootComponent->GetComponentLocation();
		ANPC_PatrolPath_CPP* NPC = world->SpawnActor<ANPC_PatrolPath_CPP>(pNPC, SpawnLocation, SpawnRotation, spawnParams);
		if (NPC)
		{
			NPC->Set_pPatrol_Path(pPatrol_Path);
			//NPC->Set_pAi_Controller(pAi_Controller);
		}
	}
}

void ANPC_SpawnerCPP::Delete_NPC()
{

}

void ANPC_SpawnerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	int32 temp = FMath::RandRange(0, 200);
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Value: %f"), temp));
	if (temp == 50)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Spawned a new NPC")));
		Add_NPC();
	}
}