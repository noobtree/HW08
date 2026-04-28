// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "HW08/PlayerEffect/StunGrenadeEffect.h"
#include "StunGrenadeItemActor.generated.h"

/**
 * 
 */
UCLASS()
class HW08_API AStunGrenadeItemActor : public AItemActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class USceneCaptureComponent2D> captureComponent;

	// 섬광탄 효과가 정의된 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StunGrenadeItem")
	TSubclassOf<UPlayerEffectData> stunEffect;

public:
	AStunGrenadeItemActor();

	// 아이템 사용자에게 효과를 적용시키는 함수
	void UseItem(APlayerCharacter* activator) override;
};
