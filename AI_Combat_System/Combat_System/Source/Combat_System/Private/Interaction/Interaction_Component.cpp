#include "../../Public/Interaction/Interaction_Component.h"

#include "Engine/Public/CollisionQueryParams.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"

#include "../../Public/Interaction/Interaction_Interface.h"
#include "../../Public/Interaction/Interactable_Component.h"


UInteraction_Component::UInteraction_Component() :
	FocusedActor(nullptr),
	fInteractionDistance(200.f)
{
	PrimaryComponentTick.bCanEverTick = true;

	TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true);
	Player = Cast<ACharacter>(GetOwner());
}

void UInteraction_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	HandleHighlight();
}

void UInteraction_Component::Interaction()
{
	if (!FocusedActor)
	{
		return;
	}

	if (UInteractable_Component* Component = Cast<UInteractable_Component>(FocusedActor->FindComponentByClass(UInteractable_Component::StaticClass())))
	{
		Component->Execute_OnInteract(Component, FocusedActor);
	}
}

void UInteraction_Component::HandleHighlight()
{
	//AActor* interactable = FindActorInLineOfSide();
	AActor* interactable = FindActorInLineOfBone("head");
	if (interactable)
	{
		if (interactable == FocusedActor)
		{
			return;
		}

		if (FocusedActor)
		{
			if (UInteractable_Component* Component = Cast<UInteractable_Component>(FocusedActor->FindComponentByClass(UInteractable_Component::StaticClass())))
			{
				Component->Execute_Focus(Component, false);
			}
		}

		if (UInteractable_Component* Component = Cast<UInteractable_Component>(interactable->FindComponentByClass(UInteractable_Component::StaticClass())))
		{
			Component->Execute_Focus(Component, true);
		}
		FocusedActor = interactable;
	}
	else
	{
		if (!FocusedActor)
		{
			return;
		}

		if (UInteractable_Component* Component = Cast<UInteractable_Component>(FocusedActor->FindComponentByClass(UInteractable_Component::StaticClass())))
		{
			Component->Execute_Focus(Component, false);
		}

		FocusedActor = nullptr;
	}
}

AActor* UInteraction_Component::FindActorInLineOfSide()
{
	FVector Location;
	FRotator Rotator{};
	FHitResult Hit(ForceInit);
	Location.Normalize();	//to unit vector as a vector initialization
	Rotator.Normalize();	//to unit vector as a vector initialization
	Player->GetController()->GetPlayerViewPoint(Location, Rotator);

	FVector start = Location;
	FVector end = start + (Rotator.Vector() * fInteractionDistance);

	GetWorld()->LineTraceSingleByChannel(Hit,
		start,
		end,
		ECC_Visibility,
		TraceParams
	);

	return Hit.GetActor();
}

AActor* UInteraction_Component::FindActorInLineOfBone(const FName& sBoneName)
{
	FVector Player_Head_Location = Player->GetMesh()->GetBoneLocation(sBoneName, EBoneSpaces::WorldSpace);
	FVector Location;
	FRotator Rotator{};
	FHitResult Hit(ForceInit);
	Location.Normalize();	//to unit vector as a vector initialization
	Rotator.Normalize();	//to unit vector as a vector initialization
	Player->GetController()->GetPlayerViewPoint(Location, Rotator);

	FVector start = Player_Head_Location + Rotator.Vector();
	Player_Head_Location.Z += 30; 
	//FVector start = Location;
	FVector end = start + (Rotator.Vector() * fInteractionDistance);

	GetWorld()->LineTraceSingleByChannel(Hit,
		start,
		end,
		ECC_Visibility,
		TraceParams
	);

	return Hit.GetActor();
}

void UInteraction_Component::BeginPlay()
{
	Super::BeginPlay();

	if (UInputComponent* PlayerInputComponent = GetOwner()->FindComponentByClass<UInputComponent>())
	{
		PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &UInteraction_Component::Interaction);
	}
}