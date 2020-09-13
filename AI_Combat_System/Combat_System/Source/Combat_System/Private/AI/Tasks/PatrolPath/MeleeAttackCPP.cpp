
#include "../../../../Public/AI/Tasks/PatrolPath/MeleeAttackCPP.h"

EBTNodeResult::Type UMeleeAttackCPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("UMeleeAttackCPP")));

	return EBTNodeResult::Type();
}