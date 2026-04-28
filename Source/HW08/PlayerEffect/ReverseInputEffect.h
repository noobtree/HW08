// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerEffectData.h"
#include "ReverseInputEffect.generated.h"

/**
 * 
 */
UCLASS()
class HW08_API UReverseInputEffect : public UPlayerEffectData
{
	GENERATED_BODY()

public:
	UReverseInputEffect();

public:
	// 특정 액터를 대상으로 플레이어 효과를 적용하는 함수
	virtual void ApplyPlayerEffect(AActor* target) const override;
	// 특정 액터를 대상으로 플레이어 효과를 제거하는 함수
	virtual void RemovePlayerEffect(AActor* target) const override;
};
