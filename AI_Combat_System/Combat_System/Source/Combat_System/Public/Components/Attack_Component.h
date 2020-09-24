
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Attack_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBAT_SYSTEM_API UAttack_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAttack_Component();

protected:

	virtual void BeginPlay() override;


		
};
