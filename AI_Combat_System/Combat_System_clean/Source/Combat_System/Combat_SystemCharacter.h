// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/Interfaces/CombatInterfaceCPP.h"
#include "Public/Base_Classes/Base_Character.h"

#include "Combat_SystemCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMeeleAttack);


class ANPC_PatrolPath_CPP;


UCLASS(config = Game)
class ACombat_SystemCharacter : public ABase_Character, public ICombatInterfaceCPP
{
	GENERATED_BODY()
	
public:
	ACombat_SystemCharacter();

	virtual void BeginPlay() override;

#pragma region Class_Components
protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowProtectedAccess = "true"))
		class UCombat_Component_CPP* pCombat_Component_CPP;

#pragma endregion
#pragma region Class_Variables
protected:

#pragma endregion
#pragma region Pre_Setup_Movement_Variables
public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

#pragma endregion
#pragma region User_Defined_Delegates


	
#pragma endregion
#pragma region Class_Getters

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

#pragma endregion
#pragma region Pre_Setup_Functions
protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
#pragma endregion
#pragma region Class_Functions
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
		void Melee_Attack();
	virtual void Melee_Attack_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
		void Block_Hit();
	virtual void Block_Hit_Implementation() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

#pragma endregion 
};