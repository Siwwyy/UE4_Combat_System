
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


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
	void Melee_Attack();

};