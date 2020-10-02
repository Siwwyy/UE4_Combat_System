
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Base_Character.generated.h"

UCLASS()
class COMBAT_SYSTEM_API ABase_Character : public ACharacter
{
	GENERATED_BODY()

public:

	ABase_Character();
	
#pragma region Class_Variables
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		bool bIsAttacked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
		float fHealth;

#pragma endregion



};
