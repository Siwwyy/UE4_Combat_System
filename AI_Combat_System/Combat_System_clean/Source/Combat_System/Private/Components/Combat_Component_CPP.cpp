

#include "Components/Combat_Component_CPP.h"
#include "Combat_System/Combat_SystemCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Engine/EngineTypes.h"
#include "TimerManager.h"


UCombat_Component_CPP::UCombat_Component_CPP()
{
	PrimaryComponentTick.bCanEverTick = false;

	/* BOX COMPONENT*/
	pBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("pBoxComponent"));
	pBoxComponent->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	pBoxComponent->SetVisibility(true);
	pBoxComponent->SetHiddenInGame(false);

	//GetWorld()->GetTimerManager().SetTimer();

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

	//GetWorld()->GetTimerManager().SetTimer();	//set timer to count time of "beeing aggressive of npc"

	pBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UCombat_Component_CPP::OnOverlapBegin);
	pBoxComponent->OnComponentEndOverlap.AddDynamic(this, &UCombat_Component_CPP::OnOverlapEnd);
}

void UCombat_Component_CPP::Receive_Damage(AActor* const HitPlayer, ABase_Character* const CompOwner)
{
	HitPlayer->TakeDamage(CompOwner->Get_fDamage(), FPointDamageEvent(), CompOwner->GetController(), CompOwner);
}

void UCombat_Component_CPP::Calm_Player(class ABase_Character* const CharacterToCalm)
{
	CharacterToCalm->SetIsAttacked(false);
}

void UCombat_Component_CPP::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())	//checking do the owner is an attacked player (prevents from self attack)
	{
		return;
	}

	if (ABase_Character* Character = Cast<ABase_Character>(GetOwner()))
	{
		ABase_Character* NPC = Cast<ABase_Character>(OtherActor);
		Receive_Damage(OtherActor, Character);

		const FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject( this, &UCombat_Component_CPP::Calm_Player, NPC );
		
		GetWorld()->GetTimerManager().SetTimer(StopWatch, RespawnDelegate, 5.0f, false);
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("OnOverlapBegin")));
	pBoxComponent->SetGenerateOverlapEvents(false);		//when I hit NPC it prevents me from i.e hitting multiple times	
}

void UCombat_Component_CPP::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == GetOwner())	//checking do the owner is an attacked player (prevents from self attack)
	{
		return;
	}

	//if (ABase_Character* Character = Cast<ABase_Character>(OtherActor))
	//{
	//	Character->SetIsAttacked(false);
	//}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("OnOverlapEnd")));

	pBoxComponent->SetGenerateOverlapEvents(false);		//when I hit NPC it prevents me from i.e hitting multiple times	
}