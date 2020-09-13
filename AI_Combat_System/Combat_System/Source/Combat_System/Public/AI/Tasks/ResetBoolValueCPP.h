
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "ResetBoolValueCPP.generated.h"


UCLASS()
class COMBAT_SYSTEM_API UResetBoolValueCPP : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
