
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Base_Character.generated.h"

#pragma region Enums

UENUM(BlueprintType, Category = "Enums")
enum class Character_Type : uint8
{
	Player = 0 UMETA(DisplayName = "Player"),
	Guard = 1 UMETA(DisplayName = "Guard"),
	Villager = 2 UMETA(DisplayName = "Villager"),
	Protector = 3 UMETA(DisplayName = "Villager"),
	Aggressor = 4 UMETA(DisplayName = "Villager"),
	Neutral = 5 UMETA(DisplayName = "Villager")
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
	Character_Type CharacterType;

#pragma endregion
#pragma region Class_Setters
public:

	UFUNCTION(BlueprintCallable, Category = "Class_Setters")
		void SetIsAttacked(bool IsAttacked);

	UFUNCTION(BlueprintCallable, Category = "Class_Setters")
		void SetHealth(float Health);

	UFUNCTION(BlueprintCallable, Category = "Class_Setters")
		void SetDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Class_Setters")
		void SetCharacter_Type(Character_Type Character_Type);

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

	UFUNCTION(BlueprintCallable, Category = "Class_Getters")
		FORCEINLINE Character_Type Get_CharacterType() const
	{
		return CharacterType;
	}

#pragma endregion
};