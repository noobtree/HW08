// Fill out your copyright notice in the Description page of Project Settings.


#include "StunGrenadeItemActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PlayerEffectManageComponent.h"

AStunGrenadeItemActor::AStunGrenadeItemActor()
{
	itemName = FName("StunGrenade");

	captureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(FName("SceneCaptureComponent2D"));
}

void AStunGrenadeItemActor::UseItem(APlayerCharacter* activator)
{
	if (activator == nullptr)
	{
		return;
	}

	// 플레이어 이펙트를 관리하는 컴포넌트 찾기
	if (UPlayerEffectManageComponent* component = activator->FindComponentByClass<UPlayerEffectManageComponent>())
	{
		if (UClass* reference = stunEffect.Get())
		{
			UStunGrenadeEffect* data = NewObject<UStunGrenadeEffect>(this, FName("StunGrenadeEffect"));

			if (data != nullptr)
			{
				// 이펙트 적용
				component->ApplyPlayerEffect(data);
				DestroyItem();
			}
		}
	}
}
