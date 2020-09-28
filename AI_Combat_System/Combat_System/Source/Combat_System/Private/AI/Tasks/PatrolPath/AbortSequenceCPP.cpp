
#include "../../../../Public/AI/Tasks/PatrolPath/AbortSequenceCPP.h"


UAbortSequenceCPP::UAbortSequenceCPP(FObjectInitializer const& object_initializer)
{

}

EBTNodeResult::Type UAbortSequenceCPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("UAbortSequenceCPP")));

	return EBTNodeResult::Type();
}