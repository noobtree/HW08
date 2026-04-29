// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameInstance.h"

UFPSGameInstance::UFPSGameInstance()
{
	score = 0;
	currentLevelIndex = 0;
}

void UFPSGameInstance::AddScore(int32 value)
{
	score += value;
	UE_LOG(LogTemp, Warning, TEXT("Current Score = %d"), score);
}

void UFPSGameInstance::InitializeGameState()
{
	score = 0;
	currentLevelIndex = 0;
}
