
#include "../../Public/Base_Classes/Base_Character.h"

#include "Containers/EnumAsByte.h"


ABase_Character::ABase_Character() :
	bIsAttacked(false),
	fHealth(100.f),
	fDamage(0.f),
	CharacterType()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABase_Character::SetIsAttacked(bool IsAttacked)
{
	bIsAttacked = IsAttacked;
}

void ABase_Character::SetHealth(float Health)
{
	fHealth = Health;
}

void ABase_Character::SetDamage(float Damage)
{
	fDamage = Damage;
}

void ABase_Character::SetCharacter_Type(::Character_Type Character_Type)
{
	CharacterType = Character_Type;
}