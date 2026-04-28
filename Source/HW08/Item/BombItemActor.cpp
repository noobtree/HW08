// Fill out your copyright notice in the Description page of Project Settings.


#include "BombItemActor.h"

ABombItemActor::ABombItemActor()
{
	itemName = FName("Bomb");
}

void ABombItemActor::UseItem(APlayerCharacter* activator)
{
	if (activator == nullptr)
	{
		return;
	}

	//GetWorld()
	DestroyItem();
}
