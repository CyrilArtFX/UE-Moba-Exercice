// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEMobaGameMode.h"
#include "UEMobaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUEMobaGameMode::AUEMobaGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
