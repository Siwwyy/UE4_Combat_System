

#include "Components/Combat_Component_CPP.h"


#include "DrawDebugHelpers.h"
#include "Combat_System/Combat_SystemCharacter.h"
#include "AI/NPC/NPC_PatrolPath_CPP.h"

#include "Components/SphereComponent.h"

#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include "Logic/Combat_System_Logic.h"

#include "Math/UnrealMathUtility.h"


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

//void UCombat_Component_CPP::Receive_Damage(AActor* const HitPlayer, ABase_Character* const CompOwner)
//
//{	if (!HitPlayer || !CompOwner)
//	{
//		return;
//	}
//	HitPlayer->TakeDamage(CompOwner->Get_fDamage(), FPointDamageEvent(), CompOwner->GetController(), CompOwner);
//}
//
//void UCombat_Component_CPP::Dodge_Damage(class ABase_Character* const CompOwner)
//{
//	if (ANPC_PatrolPath_CPP* NPC = Cast<ANPC_PatrolPath_CPP>(CompOwner))
//	{
//		NPC->Block_Hit_Implementation();
//		DrawDebugString(NPC->GetWorld(), FVector(NPC->GetActorLocation().X, NPC->GetActorLocation().Y, NPC->GetActorLocation().Z + 220.f), FString::Printf(TEXT("Current health: %f"), NPC->Get_fHealth()), 0, FColor::Red, 0.4f, false, 3.f);
//	}
//}
//
void UCombat_Component_CPP::Calm_Player(class ABase_Character* const CharacterToCalm)
{
	if (!CharacterToCalm)
	{
		return;
	}
	CharacterToCalm->SetIsAttacked(false);
	CharacterToCalm->SetIsBlockingHit(false);
}

void UCombat_Component_CPP::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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