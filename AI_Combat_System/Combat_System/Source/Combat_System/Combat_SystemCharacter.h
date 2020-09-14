// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Combat_SystemCharacter.generated.h"

DECLARE_DELEGATE_OneParam(Melee_Atack_Delegate, bool);

UCLASS(Blueprintable, config = Game)
class ACombat_SystemCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region Component_Declaration
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
#pragma endregion

public:
	ACombat_SystemCharacter();

	virtual void BeginPlay() override;

#pragma region Pre_Setup_Movement_Variables
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
#pragma endregion
	////Delegate Melee_Atack_Delegate
	//UDELEGATE(BlueprintCallable, Category = "Delegates")
	//Melee_Atack_Delegate Melee_Atack_Delegate;

	//UPROPERTY(BlueprintCallable, Category = "Delegates")
		Melee_Atack_Delegate Attack_Delegate;

protected:

#pragma region Pre_Setup_Functions
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

	//Melee Attack Function
	UFUNCTION(BlueprintCallable, Category = "Attack", meta = (AllowProtectedAccess = "true"))
		void Melee_Attack(bool bState);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:

#pragma region Pre_Setup_Getters
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
#pragma endregion

};