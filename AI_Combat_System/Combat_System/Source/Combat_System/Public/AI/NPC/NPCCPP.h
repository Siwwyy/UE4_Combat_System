
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interfaces/CombatInterfaceCPP.h"

#include "NPCCPP.generated.h"

UCLASS()
class COMBAT_SYSTEM_API ANPCCPP : public ACharacter, public ICombatInterfaceCPP
{
	GENERATED_BODY()

public:
	ANPCCPP();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Blueprintable, Category = "Attack")
		void Melee_Attack();
	virtual void Melee_Attack_Implementation() override;

protected:
	virtual void BeginPlay() override;

};
