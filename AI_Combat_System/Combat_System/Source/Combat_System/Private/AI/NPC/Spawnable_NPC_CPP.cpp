#include "../../../Public/AI/NPC/Spawnable_NPC_CPP.h"


#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"


ASpawnable_NPC_CPP::ASpawnable_NPC_CPP()
{
	PrimaryActorTick.bCanEverTick = false;

	pSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("pSceneComponent"));
	RootComponent = pSceneComponent;


	pSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("pSphereComponent"));
	pSphereComponent->InitSphereRadius(40.0f);
	pSphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	pSphereComponent->SetupAttachment(pSceneComponent);


	pStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pStaticMeshComponent"));
	pStaticMeshComponent->SetStaticMesh(pStaticMesh);
	pStaticMeshComponent->SetupAttachment(pSceneComponent);
}

void ASpawnable_NPC_CPP::BeginPlay()
{
	Super::BeginPlay();
}