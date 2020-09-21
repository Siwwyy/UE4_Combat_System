
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC_SpawnerCPP.generated.h"


class UStaticMeshComponent;
class UCharacter;
class ANPCCPP;
class ASpawnable_NPC_CPP;

UCLASS()
class COMBAT_SYSTEM_API ANPC_SpawnerCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	ANPC_SpawnerCPP();

	virtual void Tick(float DeltaTime) override;

	~ANPC_SpawnerCPP();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components_CPP", meta = (AllowProtectedAccess = "true" ))
	UStaticMeshComponent* pStatic_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components_CPP", meta = (AllowProtectedAccess = "true"))
	AActor* pPatrol_Path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC_Array_CPP", meta = (AllowProtectedAccess = "true"))
	TArray<ANPCCPP*> NPC_Array;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC_CPP", meta = (AllowProtectedAccess = "true"))
	//ACharacter* pNPC;
	//TSubclassOf<ANPCCPP> pNPC; /*ACharacter* pNPC;*/
	TSubclassOf<ASpawnable_NPC_CPP> pNPC; /*ACharacter* pNPC;*/

	//UPROPERTY(EditAnywhere, Category = "NPC_Array", meta = (AllowProtectedAccess = "true"))
	//TSubclassOf<UCharacter> Character;

	virtual void BeginPlay() override;

	void Add_NPC();
	void Delete_NPC();

};