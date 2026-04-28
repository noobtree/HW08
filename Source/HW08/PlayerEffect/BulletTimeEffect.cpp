// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTimeEffect.h"

UBulletTimeEffect::UBulletTimeEffect()
{
	effectName = FName("BulletTime");
	duration = 5;
}

void UBulletTimeEffect::ApplyPlayerEffect(AActor* target) const
{
}

void UBulletTimeEffect::RemovePlayerEffect(AActor* target) const
{
}
