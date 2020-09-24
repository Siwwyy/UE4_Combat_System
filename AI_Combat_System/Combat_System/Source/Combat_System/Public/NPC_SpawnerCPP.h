
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC_SpawnerCPP.generated.h"


class UStaticMeshComponent;
class APatrol_Path_CPP;
class ASpawnable_NPC_CPP;
class ANPC_PatrolPath_CPP;
class AAI_Controller;

UCLASS()
class COMBAT_SYSTEM_API ANPC_SpawnerCPP : public AActor
{
	GENERATED_BODY()

public:
	ANPC_SpawnerCPP();

	virtual void Tick(float DeltaTime) override;

protected:

#pragma region Class_Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components_CPP", meta = (AllowProtectedAccess = "true"))
		UStaticMeshComponent* pStatic_Mesh;

#pragma endregion
#pragma region Class_Pointers

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers", meta = (AllowProtectedAccess = "true"))
		APatrol_Path_CPP* pPatrol_Path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers", meta = (AllowProtectedAccess = "true"))
		AAI_Controller* pAi_Controller;

#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers", meta = (AllowProtectedAccess = "true"))
		TSubclassOf<ANPC_PatrolPath_CPP> pNPC;

	virtual void BeginPlay() override;

	void Add_NPC();
	void Delete_NPC();

};