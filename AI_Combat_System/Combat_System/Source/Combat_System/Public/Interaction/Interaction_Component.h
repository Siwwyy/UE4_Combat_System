
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBAT_SYSTEM_API UInteraction_Component : public UActorComponent
{
	GENERATED_BODY()

public:

	UInteraction_Component();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Interaction();

	void HandleHighlight();

	AActor* FindActorInLineOfSide();
	AActor* FindActorInLineOfBone(const FName & sBoneName);

	virtual void BeginPlay() override;

protected:
	UPROPERTY()
		AActor* FocusedActor;

	UPROPERTY()
		ACharacter* Player;	//owner of interaction component

	FCollisionQueryParams TraceParams;

	UPROPERTY(EditAnywhere, Category = "Interaction")
		float fInteractionDistance;

		
};
