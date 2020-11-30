

#include "Components/Combat_Component_CPP.h"

#include "AI/NPC/NPC_PatrolPath_CPP.h"

#include "Components/SphereComponent.h"

#include "Engine/EngineTypes.h"
#include "TimerManager.h"



UCombat_Component_CPP::UCombat_Component_CPP()
{
	PrimaryComponentTick.bCanEverTick = false;

	/* SPHERE COMPONENT*/
	pSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("pSphereComponent"));
	pSphereComponent->SetSphereRadius(10.f);
	pSphereComponent->SetVisibility(true);
	pSphereComponent->SetHiddenInGame(false);

}

void UCombat_Component_CPP::BeginPlay()
{
	Super::BeginPlay();

	pSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UCombat_Component_CPP::OnOverlapBegin);
	pSphereComponent->OnComponentEndOverlap.AddDynamic(this, &UCombat_Component_CPP::OnOverlapEnd);
}

void UCombat_Component_CPP::Calm_Player(class ABase_Character* const CharacterToCalm)
{
	if (!CharacterToCalm)
	{
		return;
	}
	CharacterToCalm->SetIsAttacked(false);
	CharacterToCalm->SetIsBlockingHit(false);
}

void UCombat_Component_CPP::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FString HitPlayer = OtherActor->GetName();
	const FString CompOwner = GetOwner()->GetName();
	if (OtherActor == GetOwner() || HitPlayer == CompOwner)	//checking do the owner is an attacked player (prevents from self attack)
	{
		return;
	}
	//

	
	if (ABase_Character* Owner = Cast<ABase_Character>(GetOwner()))
	{
		//ACombat_System_Logic::Attack_NPC(Owner);
		
		OtherActor->TakeDamage(Owner->Get_fDamage(), FPointDamageEvent(), Owner->GetController(), Owner);
		
		//Dodge_Damage(Owner);
		//Receive_Damage(OtherActor, Owner);
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("OnOverlapBegin")));
	
	pSphereComponent->SetGenerateOverlapEvents(false);		//when I hit NPC it prevents me from i.e hitting multiple times	
}

void UCombat_Component_CPP::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const FString HitPlayer = OtherActor->GetName();
	const FString CompOwner = GetOwner()->GetName();
	if (OtherActor == GetOwner() || HitPlayer == CompOwner)	//checking do the owner is an attacked player (prevents from self attack) or is the same class type
	{
		return;
	}

	if (ABase_Character* Owner = Cast<ABase_Character>(GetOwner()))
	{
		ABase_Character* Actor = Cast<ABase_Character>(OtherActor);


	///*	const int32 temp = FMath::RandRange(0, 5);
	//	if(temp == 2)
	//	{
	//		Dodge_Damage(Owner);
	//	}*/
	//	//Dodge_Damage(Owner);

		const FTimerDelegate CalmPlayerDelegate = FTimerDelegate::CreateUObject( this, &UCombat_Component_CPP::Calm_Player, Actor );
		GetWorld()->GetTimerManager().SetTimer(StopWatch, CalmPlayerDelegate, 2.0f, false);
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("OnOverlapEnd")));

	pSphereComponent->SetGenerateOverlapEvents(false);		//when I hit NPC it prevents me from i.e hitting multiple times	
}