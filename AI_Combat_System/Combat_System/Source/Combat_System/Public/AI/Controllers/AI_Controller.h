
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
	//UPROPERTY(EditAnywhere, Category = "Behavior_Type", meta = (AllowPrivateAccess = "true"))
	NPC_Character_Type type;
public:
	//UFUNCTION(BlueprintCallable, Category = "Behavior_Type")
	//void Set_Behavior_Type(enum NPC_Character_Type eType);

	UFUNCTION(BlueprintCallable, Category = "Cos")
		void Cos();


};