// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTimeItemActor.h"
#include "PlayerEffectManageComponent.h"

ABulletTimeItemActor::ABulletTimeItemActor()
{
	itemName = "BulletTime";
}

void ABulletTimeItemActor::UseItem(APlayerCharacter* activator)
{
	if (activator == nullptr)
	{
		return;
	}

	// 플레이어 이펙트를 관리하는 컴포넌트 찾기
	if (UPlayerEffectManageComponent* component = activator->FindComponentByClass<UPlayerEffectManageComponent>())
	{
		if (UClass* reference = bulletTimeEffect.Get())
		{
			UBulletTimeEffect* data = NewObject<UBulletTimeEffect>(this, FName("BulletTimeEffect"));

			if (data != nullptr)
			{
				// 이펙트 적용
				component->ApplyPlayerEffect(data);
				DestroyItem();
			}
		}
	}
}
