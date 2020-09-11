
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Interface.h"
#include "Interactable_Doors.generated.h"

UCLASS()
class COMBAT_SYSTEM_API AInteractable_Doors : public AActor, public IActor_Interface
{
	GENERATED_BODY()
	
public:
	AInteractable_Doors();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void Action();
	virtual void Action_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMesh* Door;

	float fDoor_Opening_Angle;

	bool bDoor_Condition;

private:
	void Toggle_Door();



};
