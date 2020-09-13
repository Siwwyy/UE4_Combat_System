
#include "../../../Public/AI/Tasks/FindPlayerLocationCPP.h"

EBTNodeResult::Type UFindPlayerLocationCPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("UFindPlayerLocationCPP")));

	return EBTNodeResult::Type();
}