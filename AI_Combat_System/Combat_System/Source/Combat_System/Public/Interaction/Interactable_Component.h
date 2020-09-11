
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction_Interface.h"
#include "Interactable_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBAT_SYSTEM_API UInteractable_Component : public UActorComponent, public IInteraction_Interface
{
	GENERATED_BODY()

public:

	UInteractable_Component();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void Focus(bool bState);
	virtual void Focus_Implementation(bool bState) override;

private:
	UPROPERTY()
		AActor* Owner;

		
};
