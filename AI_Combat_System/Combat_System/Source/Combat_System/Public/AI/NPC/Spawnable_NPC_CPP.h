
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Spawnable_NPC_CPP.generated.h"


class USceneComponent;
class USphereComponent;
class UStaticMeshComponent;
class UStaticMesh;


UCLASS()
class COMBAT_SYSTEM_API ASpawnable_NPC_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnable_NPC_CPP();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components_CPP", meta = (AllowProtectedAccess = "true"))
		USceneComponent* pSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components_CPP", meta = (AllowProtectedAccess = "true"))
		USphereComponent* pSphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components_CPP", meta = (AllowProtectedAccess = "true"))
		UStaticMeshComponent* pStaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components_CPP", meta = (AllowProtectedAccess = "true"))
		UStaticMesh* pStaticMesh;
};