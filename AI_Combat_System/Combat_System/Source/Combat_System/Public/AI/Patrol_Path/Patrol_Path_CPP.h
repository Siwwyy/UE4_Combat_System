
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Patrol_Path_CPP.generated.h"


class USceneComponent;


UCLASS()
class COMBAT_SYSTEM_API APatrol_Path_CPP : public AActor
{
	GENERATED_BODY()
	
public:	

	APatrol_Path_CPP();

//#pragma region Class_Getters
//
//	UFUNCTION(BlueprintCallable, Category = "Functions")
//	FORCEINLINE APatrol_Path_CPP * Get_Owner()
//	{
//		return this;
//	}
//
//#pragma endregion
protected:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowProtectedAccess = "true"))
		USceneComponent* pSceneComponent;

#pragma endregion
#pragma region Class_Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path", meta = (MakeEditWidget = "true", AllowProtectedAccess = "true"))
		TArray<FVector> Patrol_Points;

#pragma endregion
};
