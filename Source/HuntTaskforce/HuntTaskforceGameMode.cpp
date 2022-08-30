// Copyright Epic Games, Inc. All Rights Reserved.

#include "HuntTaskforceGameMode.h"
#include "HuntTaskforceHUD.h"
#include "HuntTaskforceCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHuntTaskforceGameMode::AHuntTaskforceGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AHuntTaskforceHUD::StaticClass();
}
