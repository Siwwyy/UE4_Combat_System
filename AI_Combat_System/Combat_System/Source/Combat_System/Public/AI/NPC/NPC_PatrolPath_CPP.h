
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interfaces/CombatInterfaceCPP.h"

#include "NPC_PatrolPath_CPP.generated.h"


class UMaterialInstanceDynamic;
class APatrol_Path_CPP;
class AAI_Controller;
class ACombat_SystemCharacter;


UCLASS()
class COMBAT_SYSTEM_API ANPC_PatrolPath_CPP : public ACharacter, public ICombatInterfaceCPP
{
	GENERATED_BODY()

public:

	ANPC_PatrolPath_CPP();

#pragma region Class_Functions

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Class_Functions")
		void Melee_Attack();
	virtual void Melee_Attack_Implementation() override;

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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
protected:

	virtual void BeginPlay() override;


#pragma region Class_Materials
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", meta = (AllowPrivateAccess = "true"))
		UMaterialInstanceDynamic* pDynamicMaterial;

#pragma endregion
#pragma region Class_Components
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* pBox_Component;

#pragma endregion
#pragma region Class_Pointers
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers", meta = (AllowPrivateAccess = "true"))
		APatrol_Path_CPP* pPatrol_Path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers", meta = (AllowPrivateAccess = "true"))
		AAI_Controller* pAi_Controller;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointers", meta = (AllowPrivateAccess = "true"))
	ACombat_SystemCharacter* pAttacking_Player;

#pragma endregion
#pragma region Class_Variables
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		bool bIsAttacked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
		float fHealth;

#pragma endregion
};