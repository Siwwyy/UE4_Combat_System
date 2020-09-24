
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Patrol_Path_CPP.generated.h"


class USceneComponent;


UCLASS(Blueprintable)
class COMBAT_SYSTEM_API APatrol_Path_CPP : public AActor
{
	GENERATED_BODY()
	
public:	

	APatrol_Path_CPP();

#pragma region Class_Getters

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
	FORCEINLINE bool Get_bLooping() const
	{
		return bLooping;
	}

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
	FORCEINLINE float Get_fWaitTime() const
	{
		return fWaitTime;
	}

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
	FORCEINLINE FVector Get_Patrol_Points(const int32 index) const
	{
		return Patrol_Points[index];
	}

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
	FORCEINLINE int32 Get_Patrol_Points_Size() const
	{
		return Patrol_Points.Num();
	}

#pragma endregion
protected:
#pragma region Class_Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowProtectedAccess = "true"))
		USceneComponent* pSceneComponent;

#pragma endregion
#pragma region Class_Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowProtectedAccess = "true"))
		bool bLooping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowProtectedAccess = "true"))
		float fWaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path", meta = (MakeEditWidget = "true", AllowProtectedAccess = "true"))
		TArray<FVector> Patrol_Points;

#pragma endregion
};
