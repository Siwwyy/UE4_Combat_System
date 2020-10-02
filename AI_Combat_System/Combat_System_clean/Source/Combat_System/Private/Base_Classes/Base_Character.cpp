
#include "../../Public/Base_Classes/Base_Character.h"


ABase_Character::ABase_Character() :
	bIsAttacked(false),
	fHealth(100.f)
{
	PrimaryActorTick.bCanEverTick = false;

}