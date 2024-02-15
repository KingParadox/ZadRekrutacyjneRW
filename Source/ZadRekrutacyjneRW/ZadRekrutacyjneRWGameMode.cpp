// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZadRekrutacyjneRWGameMode.h"
#include "ZadRekrutacyjneRWCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZadRekrutacyjneRWGameMode::AZadRekrutacyjneRWGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
