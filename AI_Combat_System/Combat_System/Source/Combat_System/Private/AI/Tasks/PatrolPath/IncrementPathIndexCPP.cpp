
#include "../../../../Public/AI/Tasks/PatrolPath/IncrementPathIndexCPP.h"

EBTNodeResult::Type UIncrementPathIndexCPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("UIncrementPathIndexCPP")));

	return EBTNodeResult::Type();
}