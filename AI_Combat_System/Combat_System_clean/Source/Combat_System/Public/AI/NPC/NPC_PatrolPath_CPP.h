
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Base_Classes/Base_Character.h"

#include "NPC_PatrolPath_CPP.generated.h"


UMaterialInstanceDynamic;
class APatrol_Path_CPP;
class AAI_Controller;
class ACombat_SystemCharacter;


UCLASS()
class COMBAT_SYSTEM_API ANPC_PatrolPath_CPP : public ABase_Character
{
	GENERATED_BODY()

public:

	ANPC_PatrolPath_CPP();

	virtual void BeginPlay() override;

#pragma region Class_Functions

		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

#pragma endregion
#pragma region Class_Setters

	UFUNCTION(BlueprintCallable, Category = "Class_Setters")
		void Set_pPatrol_Path(APatrol_Path_CPP* const ptr);

	UFUNCTION(BlueprintCallable, Category = "Class_Setters")
		void Set_pAi_Controller(AAI_Controller* const ptr);

#pragma endregion
#pragma region Class_Getters

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
		FORCEINLINE APatrol_Path_CPP* Get_pPatrol_Path() const
	{
		return pPatrol_Path;
	}

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
		FORCEINLINE AAI_Controller* Get_pAi_Controller() const
	{
		return pAi_Controller;
	}


#pragma endregion
#pragma region Class_Components
protected:

#pragma endregion
#pragma region Class_Pointers
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class_Pointers", meta = (AllowPrivateAccess = "true"))
		APatrol_Path_CPP* pPatrol_Path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class_Pointers", meta = (AllowPrivateAccess = "true"))
		AAI_Controller* pAi_Controller;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers", meta = (AllowPrivateAccess = "true"))
	ACombat_SystemCharacter* pAttacking_Player;

#pragma endregion
#pragma region Class_Variables
protected:

#pragma endregion
};