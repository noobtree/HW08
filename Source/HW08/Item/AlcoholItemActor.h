// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "HW08/PlayerEffect/DistortionVisionEffect.h"
#include "AlcoholItemActor.generated.h"

/**
 * 
 */
UCLASS()
class HW08_API AAlcoholItemActor : public AItemActor
{
	GENERATED_BODY()

protected:
	// 시야 왜곡 굴절 효과가 정의된 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlcoholItem")
	TSubclassOf<UPlayerEffectData> distortionEffect;

public:
	AAlcoholItemActor();

	// 아이템 사용자에게 효과를 적용시키는 함수
	void UseItem(APlayerCharacter* activator) override;
};
