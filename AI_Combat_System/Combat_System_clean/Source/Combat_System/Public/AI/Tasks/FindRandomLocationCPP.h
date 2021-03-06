
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "FindRandomLocationCPP.generated.h"


UCLASS()
class COMBAT_SYSTEM_API UFindRandomLocationCPP : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	UFindRandomLocationCPP(FObjectInitializer const& object_initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};