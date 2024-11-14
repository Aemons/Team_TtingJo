// Copyright Epic Games, Inc. All Rights Reserved.

#include "Team_TtingJoGameMode.h"
#include "Team_TtingJoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATeam_TtingJoGameMode::ATeam_TtingJoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
