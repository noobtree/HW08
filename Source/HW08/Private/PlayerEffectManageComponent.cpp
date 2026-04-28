// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerEffectManageComponent.h"

// Sets default values for this component's properties
UPlayerEffectManageComponent::UPlayerEffectManageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerEffectManageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerEffectManageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerEffectManageComponent::ApplyPlayerEffect(UPlayerEffectData* data)
{
	if (data == nullptr || data->effectName.IsNone() == true || data->duration <= 0)
	{
		return;
	}
	if (GetWorld() == nullptr)
	{
		return;
	}

	// 해당 플레이어 이펙트를 제어하는 타이머 얻기
	FPlayerEffect& effectData = activatedEffects.FindOrAdd(data->effectName);

	// 월드의 타이머 매니저 얻기
	FTimerManager& timerManager = GetWorld()->GetTimerManager();

	// 해당 효과의 남은 시간과 새로 적용할 효과의 지속 시간 비교
	float remainTime = timerManager.GetTimerRemaining(effectData.timer);
	if (remainTime < data->duration)
	{
		// 해당 플레이어 이펙트 데이터를 안정적으로 제거하기 위한 복사
		UPlayerEffectData* clone = DuplicateObject<UPlayerEffectData>(data, this);
		if (clone == nullptr)
		{
			return;
		}

		// 등록된 효과로 설정
		effectData.effect = clone;

		// 새로 적용할 효과의 지속시간이 더 크면 기존 타이머 해제
		timerManager.ClearTimer(effectData.timer);

		// 새롭게 적용되는 효과의 경우 효과 적용 함수 호출
		if (remainTime < 0)
		{
			clone->ApplyPlayerEffect(GetOwner());
		}

		// 효과 해제 예약
		FTimerDelegate delegator = FTimerDelegate::CreateUObject(this, &UPlayerEffectManageComponent::RemovePlayerEffect, clone);
		timerManager.SetTimer(effectData.timer, delegator, clone->duration, false);
	}
}

void UPlayerEffectManageComponent::RemovePlayerEffect(UPlayerEffectData* data)
{
	if (data == nullptr || GetWorld() == nullptr)
	{
		return;
	}

	FPlayerEffect effectData;

	// 적용된 효과 삭제 시도
	if (activatedEffects.RemoveAndCopyValue(data->effectName, effectData) == true)
	{
		// 타이머 해제
		GetWorld()->GetTimerManager().ClearTimer(effectData.timer);
		
		// 효과 해제 함수 호출
		effectData.effect->RemovePlayerEffect(GetOwner());
	}
}

