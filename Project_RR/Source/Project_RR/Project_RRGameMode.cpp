// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_RRGameMode.h"
#include "Project_RRCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_RRGameMode::AProject_RRGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
