
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Controller.generated.h"


class ANPC_PatrolPath_CPP;

UCLASS()
class COMBAT_SYSTEM_API AAI_Controller : public AAIController
{
	GENERATED_BODY()

public:

#pragma region Class_Getters

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
		FORCEINLINE ANPC_PatrolPath_CPP* Get_pAi_Controller() const
	{
		return pPatrolPath_NPC;
	}

#pragma endregion


private:
	enum class NPC_Character_Type
	{
		Friendly,
		Lossing_Patience,
		Aggressive
	};

#pragma region Class_Pointers

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers", meta = (AllowPrivateAccess = "true"))
		ANPC_PatrolPath_CPP* pPatrolPath_NPC;

#pragma endregion

};