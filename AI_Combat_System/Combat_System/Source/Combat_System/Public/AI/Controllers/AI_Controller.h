
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Controller.generated.h"


UCLASS()
class COMBAT_SYSTEM_API AAI_Controller : public AAIController
{
	GENERATED_BODY()
	
private:
	enum class eNPC_Character_Type : std::int8_t
	{
		Friendly,
		Lossing_Patience,
		Aggressive
	};

public:
	//UFUNCTION(BlueprintCallable, Category = "Behavior_Type")
	void Set_Behavior_Type(eNPC_Character_Type eType);

	UFUNCTION(BlueprintCallable, Category = "Cos")
	void Cos();


};