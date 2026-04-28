// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerEffectData.h"
#include "PlayerEffectManageComponent.generated.h"

USTRUCT(BlueprintType)
struct FPlayerEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPlayerEffectData> effect = nullptr;

	FTimerHandle timer;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HW08_API UPlayerEffectManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerEffectManageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// 현재 액터에게 적용된
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effect")
    TMap<FName, FPlayerEffect> activatedEffects;

public:
	// 액터에게 임의 효과를 적용하는 함수
	UFUNCTION()
	void ApplyPlayerEffect(UPlayerEffectData* data);

	UFUNCTION()
	void RemovePlayerEffect(UPlayerEffectData* data);
};
