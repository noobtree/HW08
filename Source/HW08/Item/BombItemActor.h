// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "BombItemActor.generated.h"

/**
 * 
 */
UCLASS()
class HW08_API ABombItemActor : public AItemActor
{
	GENERATED_BODY()

public:
	ABombItemActor();

	// 아이템 사용자에게 효과를 적용시키는 함수
	void UseItem(APlayerCharacter* activator) override;
};
