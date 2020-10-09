

#include "Components/Combat_Component_CPP.h"
#include "Combat_System/Combat_SystemCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


UCombat_Component_CPP::UCombat_Component_CPP()
{
	PrimaryComponentTick.bCanEverTick = false;

	/* BOX COMPONENT*/
	pBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("pBoxComponent"));
	pBoxComponent->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	pBoxComponent->SetVisibility(true);
	pBoxComponent->SetHiddenInGame(false);


	//pStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pStaticMeshComponent"));
	//if (GetOwner())
	//{
	//	GetOwner()->AddOwnedComponent(this);
	//}
	//if (ACombat_SystemCharacter* Character = Cast<ACombat_SystemCharacter>(GetOwner()))
	//{
	//	pStaticMeshComponent->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_r"));
	//}
}

void UCombat_Component_CPP::BeginPlay()
{
	Super::BeginPlay();

	pBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UCombat_Component_CPP::OnOverlapBegin);
}

void UCombat_Component_CPP::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABase_Character * Character = Cast< ABase_Character>(GetOwner()))
	{
		OtherActor->TakeDamage(Character->Get_fDamage(), FPointDamageEvent(), Character->GetController(), GetOwner());
	}
	
	pBoxComponent->SetGenerateOverlapEvents(false);
}