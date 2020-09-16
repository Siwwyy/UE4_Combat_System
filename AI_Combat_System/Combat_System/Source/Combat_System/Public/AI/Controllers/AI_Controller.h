
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Controller.generated.h"


UCLASS()
class COMBAT_SYSTEM_API AAI_Controller : public AAIController
{
	GENERATED_BODY()

private:
	enum class NPC_Character_Type
	{
		Friendly,
		Lossing_Patience,
		Aggressive
	};

};