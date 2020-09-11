// Copyright Epic Games, Inc. All Rights Reserved.

#include "Combat_SystemGameMode.h"
#include "Combat_SystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACombat_SystemGameMode::ACombat_SystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
