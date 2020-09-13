
#include "../../../../Public/AI/Tasks/PatrolPath/FindPathPointCPP.h"


EBTNodeResult::Type UFindPathPointCPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("UFindPathPointCPP")));

	return EBTNodeResult::Type();
}