
#include "AI/Tasks/PatrolPath/ChangeStatus_CPP.h"


UChangeStatus_CPP::UChangeStatus_CPP(FObjectInitializer const& object_initializer)
{

}

EBTNodeResult::Type UChangeStatus_CPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}