// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTimeEffect.h"
#include "PlayerCharacter.h"

UBulletTimeEffect::UBulletTimeEffect()
{
	effectName = FName("BulletTime");
	duration = 5;
}

void UBulletTimeEffect::ApplyPlayerEffect(AActor* target) const
{
	if (target == nullptr)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("BulletTime"));
	if (APlayerCharacter* player = CastChecked<APlayerCharacter>(target))
	{
		player->SetUseHPForAttack(false);
	}
}

void UBulletTimeEffect::RemovePlayerEffect(AActor* target) const
{
	if (target == nullptr)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Reverse"));
	if (APlayerCharacter* player = CastChecked<APlayerCharacter>(target))
	{
		player->SetUseHPForAttack(true);
	}
}
