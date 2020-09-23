
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC_PatrolPath_CPP.generated.h"

UCLASS()
class COMBAT_SYSTEM_API ANPC_PatrolPath_CPP : public ACharacter
{
	GENERATED_BODY()

public:

	ANPC_PatrolPath_CPP();

protected:

	virtual void BeginPlay() override;



};
