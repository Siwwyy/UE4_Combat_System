
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "FindPlayerLocationCPP.generated.h"


UCLASS()
class COMBAT_SYSTEM_API UFindPlayerLocationCPP : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	UFindPlayerLocationCPP(FObjectInitializer const& object_initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};