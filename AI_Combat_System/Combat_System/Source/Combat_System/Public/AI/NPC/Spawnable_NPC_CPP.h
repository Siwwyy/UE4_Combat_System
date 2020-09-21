
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawnable_NPC_CPP.generated.h"

UCLASS()
class COMBAT_SYSTEM_API ASpawnable_NPC_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnable_NPC_CPP();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components_CPP")
	UStaticMeshComponent* pStatic_Mesh;

private:	



};
