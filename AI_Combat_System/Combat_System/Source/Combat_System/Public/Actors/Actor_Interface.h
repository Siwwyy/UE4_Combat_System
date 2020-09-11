
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Actor_Interface.generated.h"


UINTERFACE(MinimalAPI)
class UActor_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMBAT_SYSTEM_API IActor_Interface
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Action();

};
