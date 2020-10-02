
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "IncrementPathIndexCPP.generated.h"


UCLASS()
class COMBAT_SYSTEM_API UIncrementPathIndexCPP : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	UIncrementPathIndexCPP(FObjectInitializer const& object_initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};