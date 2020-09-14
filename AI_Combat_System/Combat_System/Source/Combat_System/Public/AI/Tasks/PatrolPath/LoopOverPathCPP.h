
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "LoopOverPathCPP.generated.h"


UCLASS()
class COMBAT_SYSTEM_API ULoopOverPathCPP : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	ULoopOverPathCPP(FObjectInitializer const& object_initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
