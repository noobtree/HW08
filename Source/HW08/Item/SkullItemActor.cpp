// Fill out your copyright notice in the Description page of Project Settings.


#include "SkullItemActor.h"
#include "PlayerEffectManageComponent.h"

ASkullItemActor::ASkullItemActor()
{
	itemName = FName("Skull");
}

void ASkullItemActor::UseItem(APlayerCharacter* activator)
{
	if (activator == nullptr)
	{
		return;
	}

	// 플레이어 이펙트를 관리하는 컴포넌트 찾기
	if (UPlayerEffectManageComponent* component = activator->FindComponentByClass<UPlayerEffectManageComponent>())
	{
		if (UClass* reference = reverseInputEffect.Get())
		{
			UReverseInputEffect* data = NewObject<UReverseInputEffect>(this, FName("ReverseInputEffect"));

			if (data != nullptr)
			{
				// 이펙트 적용
				component->ApplyPlayerEffect(data);
				DestroyItem();
			}
		}
	}
}
