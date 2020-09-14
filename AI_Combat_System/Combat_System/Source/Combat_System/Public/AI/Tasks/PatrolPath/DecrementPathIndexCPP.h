
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "DecrementPathIndexCPP.generated.h"


UCLASS()
class COMBAT_SYSTEM_API UDecrementPathIndexCPP : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	UDecrementPathIndexCPP(FObjectInitializer const& object_initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
