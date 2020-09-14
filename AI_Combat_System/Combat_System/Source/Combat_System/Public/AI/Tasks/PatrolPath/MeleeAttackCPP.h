
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "MeleeAttackCPP.generated.h"


UCLASS()
class COMBAT_SYSTEM_API UMeleeAttackCPP : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	UMeleeAttackCPP(FObjectInitializer const & object_initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
