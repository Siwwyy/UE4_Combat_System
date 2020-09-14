
#include "../../../Public/AI/Tasks/ResetBoolValueCPP.h"


UResetBoolValueCPP::UResetBoolValueCPP(FObjectInitializer const& object_initializer)
{

}

EBTNodeResult::Type UResetBoolValueCPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("UResetBoolValueCPP")));

	return EBTNodeResult::Type();
}