
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "ChangeStatus_CPP.generated.h"


UCLASS()
class COMBAT_SYSTEM_API UChangeStatus_CPP : public UBTTask_BlueprintBase
{
	
	GENERATED_BODY()

public:
	
	UChangeStatus_CPP(FObjectInitializer const& object_initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
