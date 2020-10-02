
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TestMesh.generated.h"


class USceneComponent;
class USphereComponent;
class UStaticMeshComponent;
class UStaticMesh;
class UMaterialInstanceDynamic;


UCLASS()
class COMBAT_SYSTEM_API ATestMesh : public AActor
{
	GENERATED_BODY()

public:
	ATestMesh();

	virtual void Tick(float DeltaTime) override;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components_CPP", meta = (AllowProtectedAccess = "true"))
		UMaterialInstanceDynamic* pDynamicMaterial;
};