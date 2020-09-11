
#include "../../Public/Actors/Interactable_Lights.h"

#include "Engine/PointLight.h"

AInteractable_Lights::AInteractable_Lights() :
	Lights(),
	bLight_condition(true)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractable_Lights::Action_Implementation()
{
	bLight_condition = !bLight_condition;
	for (const auto& Light : Lights)
	{
		if (!Light)
		{
			continue;
		}
		Light->SetBrightness(bLight_condition ? 10.f : 0.f);
	}
}