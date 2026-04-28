// Fill out your copyright notice in the Description page of Project Settings.


#include "AlcoholItemActor.h"
#include "PlayerEffectManageComponent.h"

AAlcoholItemActor::AAlcoholItemActor()
{
	itemName = FName("Alcohol");
}

void AAlcoholItemActor::UseItem(APlayerCharacter* activator)
{
	if (activator == nullptr)
	{
		return;
	}

	// 플레이어 이펙트를 관리하는 컴포넌트 찾기
	if (UPlayerEffectManageComponent* component = activator->FindComponentByClass<UPlayerEffectManageComponent>())
	{
		if (UClass* reference = distortionEffect.Get())
		{
			UDistortionVisionEffect* data = NewObject<UDistortionVisionEffect>(this, FName("DistortionVisionEffect"));

			if (data != nullptr)
			{
				// 이펙트 적용
				component->ApplyPlayerEffect(data);
				DestroyItem();
			}
		}
	}
}
