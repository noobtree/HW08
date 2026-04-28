// Fill out your copyright notice in the Description page of Project Settings.


#include "HealItemActor.h"
#include "Kismet/GameplayStatics.h"
#include "HasHitPoint.h"

AHealItemActor::AHealItemActor()
{
	healAmount = 100;
}

void AHealItemActor::UseItem(APlayerCharacter* activator)
{
	// nullptr 확인
	if (activator != nullptr)
	{
		// TakeDamage 함수를 통해 체력 회복
		UGameplayStatics::ApplyDamage(activator, -healAmount, nullptr, this, NULL);

		// 아이템 액터 삭제
		DestroyItem();
	}
}
