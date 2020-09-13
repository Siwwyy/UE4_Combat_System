
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "FindPathPointCPP.generated.h"


UCLASS()
class COMBAT_SYSTEM_API UFindPathPointCPP : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
