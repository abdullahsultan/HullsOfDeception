// Copyright Epic Games, Inc. All Rights Reserved.

#include "HullsOfDeceptionGameMode.h"
#include "HullsOfDeceptionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHullsOfDeceptionGameMode::AHullsOfDeceptionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
