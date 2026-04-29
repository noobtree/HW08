// Fill out your copyright notice in the Description page of Project Settings.


#include "ReverseInputEffect.h"
#include "PlayerCharacter.h"

UReverseInputEffect::UReverseInputEffect()
{
	effectName = FName("ReverseInput");
	duration = 5;
}

void UReverseInputEffect::ApplyPlayerEffect(AActor* target) const
{
	if (target == nullptr)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Reverse Input"));
	if (APlayerCharacter* player = CastChecked<APlayerCharacter>(target))
	{
		player->SetReverseInput(true);
	}
}

void UReverseInputEffect::RemovePlayerEffect(AActor* target) const
{
	if (target == nullptr)
	{
		return;
	}

	if (APlayerCharacter* player = CastChecked<APlayerCharacter>(target))
	{
		player->SetReverseInput(false);
	}
}
