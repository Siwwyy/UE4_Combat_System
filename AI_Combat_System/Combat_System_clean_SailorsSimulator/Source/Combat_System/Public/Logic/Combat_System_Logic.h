
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Combat_System_Logic.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnOverlapBeginDelegate, UPrimitiveComponent* ,OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult);


UCLASS()
class COMBAT_SYSTEM_API ACombat_System_Logic : public AActor
{
	GENERATED_BODY()
	
#pragma region Class_Constructors_Public
public:

	ACombat_System_Logic();

#pragma endregion
#pragma region Class_Constructors_Protected
protected:

	

#pragma endregion
#pragma region Class_Variables_Public
public:

	

#pragma endregion 
#pragma region Class_Variables_Protected
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Class_Variables_Protected", meta = (AllowProtectedAccess = "true"))
	TArray<class ANPC_PatrolPath_CPP*> NPC_Array;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Class_Variables_Protected", meta = (AllowProtectedAccess = "true"))
	class ACombat_SystemCharacter * pPlayer;

#pragma endregion
#pragma region Class_Components_Public
public:

	

#pragma endregion
#pragma region Class_Components_Protected
protected:

	

#pragma endregion
#pragma region Class_Functions_Public
public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Class_Functions_Public")
	void Add_NPC(class ANPC_PatrolPath_CPP* const NPC);

	UFUNCTION(BlueprintCallable, Category = "Class_Functions_Public")
	void Remove_NPC(class ANPC_PatrolPath_CPP* const NPC);

	UFUNCTION(BlueprintCallable, Category = "Class_Functions_Public")
	void Add_Player(class ACombat_SystemCharacter* const Player);

	UFUNCTION(BlueprintCallable, Category = "Class_Functions_Public")
	void Remove_Player();

	//UFUNCTION(BlueprintCallable, Category = "Class_Functions_Public")
	static void Attack_NPC(class ABase_Character* const NPC);
	//void Attack_NPC(class ANPC_PatrolPath_CPP* const NPC, class ACombat_SystemCharacter * const DamageCauser);

#pragma endregion
#pragma region Class_Functions_Protected
protected:

	

#pragma endregion
#pragma region Class_Delegates_Public
public:
	
#pragma endregion
#pragma region Class_Delegates_Protected
protected:

	UPROPERTY(BlueprintAssignable, Category = "Class_Delegates_Protected", meta = (AllowProtectedAccess = "true"))
	FOnOverlapBeginDelegate OnOverlapBeginDelegate;
	
#pragma endregion
#pragma region Class_Setters_Public
public:

	

#pragma endregion
#pragma region Class_Setters_Protected
protected:

	

#pragma endregion 
#pragma region Class_Getters_Public 
public:

	

#pragma endregion
#pragma region Class_Getters_Protected
protected:

	

#pragma endregion
};