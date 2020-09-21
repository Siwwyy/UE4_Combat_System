//#include "../../../Public/AI/NPC/Spawnable_NPC_CPP.h"
#include "../../../Public/AI/NPC/Spawnable_NPC_CPP.h"

ASpawnable_NPC_CPP::ASpawnable_NPC_CPP()
{
	PrimaryActorTick.bCanEverTick = false;
	pStatic_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = pStatic_Mesh;
}

void ASpawnable_NPC_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}