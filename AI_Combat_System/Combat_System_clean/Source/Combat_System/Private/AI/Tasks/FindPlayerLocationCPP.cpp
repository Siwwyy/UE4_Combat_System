
#include "../../../Public/AI/Tasks/FindPlayerLocationCPP.h"

UFindPlayerLocationCPP::UFindPlayerLocationCPP(FObjectInitializer const& object_initializer)
{

}

EBTNodeResult::Type UFindPlayerLocationCPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("UFindPlayerLocationCPP")));

	return EBTNodeResult::Type();
}

void UFindPlayerLocationCPP::SetSightRange(AAIController* Controller, float SightRange)
{
   
}