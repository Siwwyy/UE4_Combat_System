
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC_SpawnerCPP.generated.h"


class UStaticMeshComponent;
class APatrol_Path_CPP;
class ANPC_PatrolPath_CPP;

UCLASS()
class COMBAT_SYSTEM_API ANPC_SpawnerCPP : public AActor
{
	GENERATED_BODY()

public:
	ANPC_SpawnerCPP();

	virtual void Tick(float DeltaTime) override;

protected:

#pragma region Class_Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class_Components", meta = (AllowProtectedAccess = "true"))
		UStaticMeshComponent* pStatic_Mesh;

#pragma endregion
#pragma region Class_Pointers

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class_Pointers", meta = (AllowProtectedAccess = "true"))
		APatrol_Path_CPP* pPatrol_Path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class_Pointers", meta = (AllowProtectedAccess = "true"))
		TSubclassOf<ANPC_PatrolPath_CPP> pNPC;

#pragma endregion
#pragma region Class_Functions

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Class_Functions")
	void Spawn_NPC();

	UFUNCTION(BlueprintCallable, Category = "Class_Functions")
	void Delete_NPC();

#pragma endregion
};