
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "AbortSequenceCPP.generated.h"

UCLASS()
class COMBAT_SYSTEM_API UAbortSequenceCPP : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	UAbortSequenceCPP(FObjectInitializer const& object_initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};