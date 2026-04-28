// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerCharacter.h"
#include "ItemBase.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemBase : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HW08_API IItemBase
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/// <summary>
	/// 아이템 사용 시의 동작을 정의하는 함수
	/// </summary>
	/// <param name="activator">아이템을 사용한 플레이어</param>
	virtual void UseItem(APlayerCharacter* activator) = 0;

	/// <summary>
	/// 아이템 주변으로 액터가 다가왔을 경우의 동작을 정의하는 함수
	/// </summary>
	/// <param name="overlapComponent">BeginOverlap 이벤트를 발생시킨 아이템 자신의 컴포넌트</param>
	/// <param name="otherActor">BeginOverlap 이벤트를 발생시킨 다른 액터</param>
	/// <param name="otherComponent">BeginOverlap 이벤트를 발생시킨 다른 액터의 컴포넌트</param>
	/// <param name="otherBodyIndex"></param>
	/// <param name="bFromSweep"></param>
	/// <param name="sweepResult"></param>
	virtual void OnItemBeginOverlap(UPrimitiveComponent* overlapComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult) = 0;
};
