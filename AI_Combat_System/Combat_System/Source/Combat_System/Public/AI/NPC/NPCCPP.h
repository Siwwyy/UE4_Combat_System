
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interfaces/CombatInterfaceCPP.h"

#include "NPCCPP.generated.h"

class AActor;

UCLASS()
class COMBAT_SYSTEM_API ANPCCPP : public ACharacter, public ICombatInterfaceCPP
{
	GENERATED_BODY()

public:
	ANPCCPP();
	ANPCCPP(const FVector & Spawn_Location, const FRotator& Spawn_Rotation);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
		void Melee_Attack();
	virtual void Melee_Attack_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void NCP_is_Attacked();

	UFUNCTION(BlueprintCallable, Category = "Setters_CPP")
	void Set_pPatrol_Path(AActor * pAActor);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components_CPP", meta = (AllowProtectedAccess = "true"))
	AActor* pPatrol_Path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components_CPP", meta = (AllowProtectedAccess = "true"))
	UStaticMeshComponent* pStatic_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowProtectedAccess = "true"))
	bool bIsAttacked;

	virtual void BeginPlay() override;

};