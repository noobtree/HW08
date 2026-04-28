// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "HW08/PlayerEffect/ReverseInputEffect.h"
#include "SkullItemActor.generated.h"

/**
 * 
 */
UCLASS()
class HW08_API ASkullItemActor : public AItemActor
{
	GENERATED_BODY()

protected:
	// 입력 반전 효과가 정의된 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkullItem")
	TSubclassOf<UPlayerEffectData> reverseInputEffect;

public:
	ASkullItemActor();

	// 아이템 사용자에게 효과를 적용시키는 함수
	void UseItem(APlayerCharacter* activator) override;
};
