// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerEffectData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, Abstract)
class HW08_API UPlayerEffectData : public UObject
{
	GENERATED_BODY()
	
public:
	// 플레이어 효과 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	FName effectName = "";

	// 플레이어 효과 지속 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	float duration = 1;

	// 플레이어 효과 아이콘
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	TObjectPtr<UTexture2D> effectIcon = nullptr;

public:
	// 특정 액터를 대상으로 플레이어 효과를 적용하는 함수
	virtual void ApplyPlayerEffect(AActor* target) const;
	// 특정 액터를 대상으로 플레이어 효과를 제거하는 함수
	virtual void RemovePlayerEffect(AActor* target) const;
};