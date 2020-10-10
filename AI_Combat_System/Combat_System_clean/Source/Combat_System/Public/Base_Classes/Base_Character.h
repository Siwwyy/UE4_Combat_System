
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Base_Character.generated.h"

#pragma region Enums

UENUM(BlueprintType, Category = "Enums")
enum class Character_Type : uint8
{
	Guard = 0 UMETA(DisplayName = "Guard"),
	Villager = 1 UMETA(DisplayName = "Villager")
};

UENUM(BlueprintType, Category = "Enums")
enum class Character_Behavior : uint8
{
	Neutral = 0 UMETA(DisplayName = "Neutral"),
	Curious = 1 UMETA(DisplayName = "Curious"),
	Aggressive = 2 UMETA(DisplayName = "Aggressive")
};

#pragma endregion

UCLASS()
class COMBAT_SYSTEM_API ABase_Character : public ACharacter
{
	GENERATED_BODY()

public:

	ABase_Character();




#pragma region Class_Variables
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowProtectedAccess = "true"))
		bool bIsAttacked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowProtectedAccess = "true"))
		float fHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowProtectedAccess = "true"))
		float fDamage;

#pragma endregion
#pragma region Class_Enums
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character_Type", meta = (AllowProtectedAccess = "true"))
	Character_Type Character_Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character_Behavior", meta = (AllowProtectedAccess = "true"))
	Character_Behavior Character_Behavior;

#pragma endregion
#pragma region Class_Setters
public:

	UFUNCTION(BlueprintCallable, Category = "Class_Setters")
		void SetIsAttacked(bool IsAttacked);

	UFUNCTION(BlueprintCallable, Category = "Class_Setters")
		void SetHealth(float Health);

	UFUNCTION(BlueprintCallable, Category = "Class_Setters")
		void SetDamage(float Damage);

#pragma endregion
#pragma region Class_Getters
public:

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
		FORCEINLINE bool Get_bIsAttacked() const
	{
		return bIsAttacked;
	}

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
		FORCEINLINE float Get_fHealth() const
	{
		return fHealth;
	}

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
		FORCEINLINE float Get_fDamage() const
	{
		return fDamage;
	}

#pragma endregion
};