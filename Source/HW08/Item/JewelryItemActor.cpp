// Fill out your copyright notice in the Description page of Project Settings.


#include "JewelryItemActor.h"
#include "FPSGameState.h"

AJewelryItemActor::AJewelryItemActor()
{
	scoreAmount = 100;
}

void AJewelryItemActor::UseItem(APlayerCharacter* activator)
{
	if (activator != nullptr)
	{
		if (AFPSGameState* gamestate = GetWorld()->GetGameStateChecked<AFPSGameState>())
		{
			gamestate->AddScore(scoreAmount);
			DestroyItem();
		}
	}
}
