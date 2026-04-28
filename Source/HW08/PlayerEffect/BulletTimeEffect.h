// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerEffectData.h"
#include "BulletTimeEffect.generated.h"

/**
 * 
 */
UCLASS()
class HW08_API UBulletTimeEffect : public UPlayerEffectData
{
	GENERATED_BODY()

public:
	UBulletTimeEffect();

public:
	// 특정 액터를 대상으로 플레이어 효과를 적용하는 함수
	virtual void ApplyPlayerEffect(AActor* target) const override;
	// 특정 액터를 대상으로 플레이어 효과를 제거하는 함수
	virtual void RemovePlayerEffect(AActor* target) const override;
};
