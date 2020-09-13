
#include "../../../../Public/AI/Tasks/PatrolPath/LoopOverPathCPP.h"

EBTNodeResult::Type ULoopOverPathCPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("ULoopOverPathCPP")));

	return EBTNodeResult::Type();
}