
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterfaceCPP.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UCombatInterfaceCPP : public UInterface
{
	GENERATED_BODY()
};


class COMBAT_SYSTEM_API ICombatInterfaceCPP
{
	GENERATED_BODY()



//#pragma region Class_Variables
//
//protected:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Class_Variables")
//	float fHit_Points;
//	
//#pragma endregion
#pragma region Class_Functions

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
	void Melee_Attack();
	
#pragma endregion
};