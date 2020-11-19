
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Controller.generated.h"


class ANPC_PatrolPath_CPP;

UCLASS()
class COMBAT_SYSTEM_API AAI_Controller : public AAIController
{
	GENERATED_BODY()

#pragma region Class_Constructors_Public
	
		AAI_Controller(const FObjectInitializer& ObjectInitializer);
	
#pragma endregion
#pragma region Class_Pointers_Protected
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class_Pointers_Protected", meta = (AllowProtectedAccess = "true"))
		ANPC_PatrolPath_CPP* pPatrolPath_NPC;

#pragma endregion
private:
	enum class NPC_Character_Type
	{
		Friendly,
		Lossing_Patience,
		Aggressive
	};

#pragma region Class_Getters_Public
public:

	UFUNCTION(BlueprintCallable, Category = "Class_Getters_Public")
		FORCEINLINE ANPC_PatrolPath_CPP* Get_pAi_Controller() const
	{
		return pPatrolPath_NPC;
	}

#pragma endregion
};