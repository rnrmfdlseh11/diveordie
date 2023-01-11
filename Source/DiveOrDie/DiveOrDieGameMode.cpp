// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiveOrDieGameMode.h"
#include "DiveOrDieCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADiveOrDieGameMode::ADiveOrDieGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
