
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interfaces/CombatInterfaceCPP.h"

#include "NPC_PatrolPath_CPP.generated.h"


class UMaterialInstanceDynamic;
class APatrol_Path_CPP;


UCLASS()
class COMBAT_SYSTEM_API ANPC_PatrolPath_CPP : public ACharacter, public ICombatInterfaceCPP
{
	GENERATED_BODY()

public:

	ANPC_PatrolPath_CPP();

#pragma region Class_Functions

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Functions")
		void Melee_Attack();
	virtual void Melee_Attack_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void NCP_is_Attacked();

#pragma endregion
#pragma region Class_Getters

	UFUNCTION(BlueprintCallable, Category = "Functions")
	FORCEINLINE APatrol_Path_CPP* Get_pPatrol_Path() const
	{
		return pPatrol_Path;
	}

#pragma endregion

protected:

	virtual void BeginPlay() override;

private:
#pragma region Class_Materials

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", meta = (AllowPrivateAccess = "true"))
		UMaterialInstanceDynamic* pDynamicMaterial;

#pragma endregion
#pragma region Class_Components


#pragma endregion
#pragma region Class_Pointers

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers", meta = (AllowPrivateAccess = "true"))
		APatrol_Path_CPP* pPatrol_Path;

#pragma endregion
#pragma region Class_Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		bool bIsAttacked;

#pragma endregion
};