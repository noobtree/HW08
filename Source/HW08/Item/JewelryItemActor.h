// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "JewelryItemActor.generated.h"

/**
 * 
 */
UCLASS()
class HW08_API AJewelryItemActor : public AItemActor
{
	GENERATED_BODY()

protected:
	// 체력 회복량
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealItem")
	float scoreAmount;

public:
	AJewelryItemActor();

	// 아이템 사용자에게 효과를 적용시키는 함수
	void UseItem(APlayerCharacter* activator) override;
};
