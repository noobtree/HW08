// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameMode.h"
#include "PlayerCharacter.h"
#include "FPSController.h"
#include "FPSGameState.h"

AFPSGameMode::AFPSGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AFPSController::StaticClass();
	GameStateClass = AFPSGameState::StaticClass();
}
