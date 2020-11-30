
#include "../../Public/Actors/Interactable_Doors.h"


AInteractable_Doors::AInteractable_Doors() :
	fDoor_Opening_Angle(90.f),
	bDoor_Condition(false)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractable_Doors::Action_Implementation()
{
	Toggle_Door();
}

void AInteractable_Doors::Toggle_Door()
{
	FRotator New_Rotation = GetActorRotation();
	bDoor_Condition = !bDoor_Condition;
	bDoor_Condition ? New_Rotation.Yaw += fDoor_Opening_Angle : New_Rotation.Yaw -= fDoor_Opening_Angle;
	SetActorRotation(New_Rotation);
}