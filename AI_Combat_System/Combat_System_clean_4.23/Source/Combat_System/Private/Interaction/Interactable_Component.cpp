
#include "../../Public/Interaction/Interactable_Component.h"

#include "../../Public/Actors/Actor_Interface.h"


UInteractable_Component::UInteractable_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
	Owner = Cast<AActor>(GetOwner());
}

void UInteractable_Component::OnInteract_Implementation(AActor* Caller)
{
	if (!Owner)
	{
		return;
	}

	if (IActor_Interface* Interface = Cast<IActor_Interface>(Owner))
	{
		Interface->Execute_Action(Owner);
	}
}

void UInteractable_Component::Focus_Implementation(bool bState)
{
	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, bState ? FString::Printf(TEXT("Focused on")) : FString::Printf(TEXT("Focused off")));
}