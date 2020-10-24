
#include "../../Public/Base_Classes/Base_Character.h"

#include "Components/Combat_Component_CPP.h"

#include "DrawDebugHelpers.h"


ABase_Character::ABase_Character() :
	bIsAttacked(false),
	fHealth(100.f),
	fDamage(0.f),
	pDynamicMaterial(nullptr),
	CharacterType()
{
	PrimaryActorTick.bCanEverTick = false;

	pCombat_Component_CPP = CreateDefaultSubobject<UCombat_Component_CPP>(TEXT("pCombat_Component_CPP"));

}

void ABase_Character::BeginPlay()
{
	Super::BeginPlay();

	pDynamicMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);	  //create instance of dynamic material
}

void ABase_Character::Melee_Attack_Implementation()
{
	if (ICombatInterfaceCPP* Interface = Cast<ICombatInterfaceCPP>(this))
	{
		Interface->Execute_Melee_Attack(this);
	}
}

void ABase_Character::Block_Hit_Implementation()
{
	if (ICombatInterfaceCPP* Interface = Cast<ICombatInterfaceCPP>(this))
	{
		IsBlockingHit = true;
		Interface->Execute_Block_Hit(this);
	}
}

float ABase_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	/*if (CharacterType != Character_Type::Aggressor)
	{
		bIsAttacked = true;
	}

	if (IsBlockingHit == false)
	{
		fHealth -= DamageAmount;
	}*/

	if (IsBlockingHit == false)
	{
		fHealth -= DamageAmount;
	}

	DrawDebugString(GetWorld(), FVector(DamageCauser->GetActorLocation().X, DamageCauser->GetActorLocation().Y, DamageCauser->GetActorLocation().Z + 120.f), FString::Printf(TEXT("Current health: %f"), fHealth), 0, FColor::Orange, 0.4f, false, 3.f);

	if (fHealth <= 0.f)
	{
		Destroy();
	}

	return ActualDamage;
}

void ABase_Character::SetIsAttacked(bool IsAttacked)
{
	bIsAttacked = IsAttacked;
}

void ABase_Character::SetIsBlockingHit(bool BlockingHit)
{
	IsBlockingHit = BlockingHit;
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
	//if (CharacterType == Character_Type::Aggressor)
	//{
	//	SetIsAttacked(true);
	//}
	//else
	//{
	//	SetIsAttacked(false);
	//}
	CharacterType = Character_Type;
}