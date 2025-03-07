// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LineTracer.h"
#include "LineTracerGameMode.h"
#include "LineTracerHUD.h"
#include "LineTracerCharacter.h"

ALineTracerGameMode::ALineTracerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALineTracerHUD::StaticClass();
}
