
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Interface.h"
#include "Interactable_Lights.generated.h"

class APointLight;

UCLASS()
class COMBAT_SYSTEM_API AInteractable_Lights : public AActor, public IActor_Interface
{
	GENERATED_BODY()
	
public:
	AInteractable_Lights();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void Action();
	virtual void Action_Implementation() override;

private:
	UPROPERTY(EditAnywhere, Category = "Light")
		TArray<APointLight*> Lights;

	bool bLight_condition;

};