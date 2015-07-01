// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "AliensVsSoldiers.h"
#include "AliensVsSoldiersGameMode.h"
#include "AliensVsSoldiersPlayerController.h"
#include "AliensVsSoldiersCharacter.h"

AAliensVsSoldiersGameMode::AAliensVsSoldiersGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAliensVsSoldiersPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}