
#include "../../../../Public/AI/Tasks/PatrolPath/DecrementPathIndexCPP.h"


UDecrementPathIndexCPP::UDecrementPathIndexCPP(FObjectInitializer const& object_initializer)
{

}

EBTNodeResult::Type UDecrementPathIndexCPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("UDecrementPathIndexCPP")));

	return EBTNodeResult::Type();
}