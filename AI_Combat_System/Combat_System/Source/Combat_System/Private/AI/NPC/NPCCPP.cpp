

#include "../../../Public/AI/NPC/NPCCPP.h"


ANPCCPP::ANPCCPP():
	bIsAttacked(false)
{
	PrimaryActorTick.bCanEverTick = false;

	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	pStatic_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

void ANPCCPP::Melee_Attack_Implementation()
{
	if (ICombatInterfaceCPP* Interface = Cast<ICombatInterfaceCPP>(this))
	{
		Interface->Execute_Melee_Attack(this);

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("ANPCCPP Attack")));
	}
}

void ANPCCPP::NCP_is_Attacked()
{
	bIsAttacked = true;
}

void ANPCCPP::Set_pPatrol_Path(AActor* pAActor)
{
	pPatrol_Path = pAActor;
}

void ANPCCPP::BeginPlay()
{
	Super::BeginPlay();
}

ANPCCPP::ANPCCPP(const FVector& Spawn_Location, const FRotator& Spawn_Rotation) :
	bIsAttacked(false)
{
	PrimaryActorTick.bCanEverTick = false;
	//RootComponent->GetOwner()->SetActorLocation(Spawn_Location);
	//RootComponent->GetOwner()->SetActorRotation(Spawn_Rotation);
}

void ANPCCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}