
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat_Component_CPP.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COMBAT_SYSTEM_API UCombat_Component_CPP : public UActorComponent
{
	GENERATED_BODY()

#pragma region Class_Constructors
public:

	UCombat_Component_CPP();

#pragma endregion
#pragma region Class_Variables
protected:

		FTimerHandle StopWatch;

#pragma endregion 
#pragma region Class_Components
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowProtectedAccess = "true"))
		class UBoxComponent* pBoxComponent;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowProtectedAccess = "true"))
		class USphereComponent* pBoxComponent;*/

#pragma endregion 
#pragma region Class_Functions
protected:

	virtual void BeginPlay() override;

	void Receive_Damage(AActor* const HitPlayer, class ABase_Character* const CompOwner);

	void Calm_Player(class ABase_Character* const CharacterToCalm);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion
#pragma region Class_Setters
public:



#pragma endregion 
#pragma region Class_Getters
public:

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
		FORCEINLINE class UBoxComponent* Get_pBoxComponent() const
	{
		return pBoxComponent;
	}

#pragma endregion 
};