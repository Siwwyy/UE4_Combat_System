
#include "Math/UnrealMathUtility.h"

#include "../Public/NPC_SpawnerCPP.h"

#include "../Public/AI/NPC/NPCCPP.h"
#include "../Public/AI/NPC/Spawnable_NPC_CPP.h"

ANPC_SpawnerCPP::ANPC_SpawnerCPP() :
	pStatic_Mesh(CreateDefaultSubobject<UStaticMeshComponent>("UStaticMeshComponent")),
	pPatrol_Path(nullptr),
	NPC_Array({}),
	pNPC(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANPC_SpawnerCPP::BeginPlay()
{
	Super::BeginPlay();

}

void ANPC_SpawnerCPP::Add_NPC()
{
	//FVector SpawnLocation = RootComponent->GetOwner()->GetActorLocation();
	//FRotator SpawnRotation = RootComponent->GetOwner()->GetActorRotation();
	//SpawnLocation.X = 1620.f;	//currently by default value and spawner location, in front of cause spawner is aroud to 1550.f on X axis
	//ANPCCPP Temp(SpawnLocation, SpawnRotation);
	//ANPCCPP Temp;
	//ANPCCPP* SpawnedCharacter = GetWorld()->SpawnActor< ANPCCPP>(Temp, SpawnLocation, SpawnRotation, FActorSpawnParameters());
	//NPC_Array.Add(&Temp);
	//auto MyCharacter = GetWorld()->SpawnActor(ANPCCPP::StaticClass());

	//ANPCCPP* MyCharacter = GetWorld()->SpawnActor< ANPCCPP >(ANPCCPP::StaticClass(), SpawnLocation, SpawnRotation);
	static int counter = 0;
	//if (counter == 9)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("counter == %d"), counter));
	//}
	//pNPC = GetWorld()->SpawnActor< ANPCCPP >(ANPCCPP::StaticClass(), SpawnLocation, SpawnRotation);
	//pNPC->Set_pPatrol_Path(pPatrol_Path);
	//++counter;

	//UWorld* world = GetWorld();
	//if (pNPC && world)
	//{
	//	FActorSpawnParameters spawnParams;
	//	spawnParams.Owner = this;

	//	//FRotator SpawnRotation(0.f,0.f,90.f);
	//	FRotator SpawnRotation(0.f,0.f,0.f);
	//	//FVector SpawnLocation(-1880.f, -3080.f, 218.f);
	//	FVector SpawnLocation = RootComponent->GetComponentLocation();
	//	ANPCCPP* NPC = world->SpawnActor<ANPCCPP>(pNPC, SpawnLocation, SpawnRotation, spawnParams);
	//	//if ( = Cast<ANPCCPP>(pNPC))
	//	if(NPC)
	//	{
	//		NPC->Set_pPatrol_Path(pPatrol_Path);
	//		NPC->SetActorRotation(FRotator(0.f, 90.f, 90.f));
	//	}
	//
	//}

	UWorld* world = GetWorld();
	if (pNPC && world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		//FRotator SpawnRotation(0.f,0.f,90.f);
		FRotator SpawnRotation(0.f, 0.f, 0.f);
		//FVector SpawnLocation(-1880.f, -3080.f, 218.f);
		FVector SpawnLocation = RootComponent->GetComponentLocation();
		ASpawnable_NPC_CPP* NPC = world->SpawnActor<ASpawnable_NPC_CPP>(pNPC, SpawnLocation, SpawnRotation, spawnParams);
		//if ( = Cast<ANPCCPP>(pNPC))
		if (NPC)
		{
			//NPC->Set_pPatrol_Path(pPatrol_Path);
			//NPC->SetActorRotation(FRotator(0.f, 90.f, 90.f));
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

ANPC_SpawnerCPP::~ANPC_SpawnerCPP()
{
	NPC_Array.Empty();
}