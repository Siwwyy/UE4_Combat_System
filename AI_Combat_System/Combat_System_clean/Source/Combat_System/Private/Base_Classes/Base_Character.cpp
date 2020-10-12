
#include "../../Public/Base_Classes/Base_Character.h"

#include "Components/Combat_Component_CPP.h"

#include "DrawDebugHelpers.h"
#include "TimerManager.h"


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
		Interface->Execute_Block_Hit(this);
	}
}

float ABase_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	bIsAttacked = true;
	fHealth -= DamageAmount;

	DrawDebugString(GetWorld(), DamageCauser->GetActorLocation(), FString::Printf(TEXT("Current Class health: %f"), fHealth), 0, FColor::Blue, 0.4f, false, 3.f);

	if (fHealth <= 0.f)
	{
		Destroy();
	}

	return ActualDamage;
}

void ABase_Character::Making_Furious()
{

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