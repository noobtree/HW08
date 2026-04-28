// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "HW08/PlayerEffect/BulletTimeEffect.h"
#include "BulletTimeItemActor.generated.h"

/**
 * 
 */
UCLASS()
class HW08_API ABulletTimeItemActor : public AItemActor
{
	GENERATED_BODY()

protected:
	// 무한 총알 효과가 정의된 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletTimeItem")
	TSubclassOf<UPlayerEffectData> bulletTimeEffect;

public:
	ABulletTimeItemActor();

	// 아이템 사용자에게 효과를 적용시키는 함수
	void UseItem(APlayerCharacter* activator) override;
};
