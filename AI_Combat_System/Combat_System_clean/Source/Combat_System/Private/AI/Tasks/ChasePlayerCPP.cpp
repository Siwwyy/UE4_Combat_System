
#include "../../../Public/AI/Tasks/ChasePlayerCPP.h"

UChasePlayerCPP::UChasePlayerCPP(FObjectInitializer const& object_initializer)
{

}

EBTNodeResult::Type UChasePlayerCPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("UChasePlayerCPP")));

	return EBTNodeResult::Type();
}