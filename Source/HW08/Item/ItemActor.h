// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.h"
#include "ItemActor.generated.h"

UCLASS()
class HW08_API AItemActor : public AActor, public IItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
#pragma region Components

	// root 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> defaultSceneRoot;

	// 아이템의 Collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> collision;

	// 아이템의 스태틱 메쉬를 관리하는 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> meshComponent;

#pragma endregion

#pragma region General Settings

	// 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings");
	FName itemName;

	// 액터가 생성된 시점부터 측정하는 아이템의 수명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings");
	float lifeTime;

	// 플레이어 캐릭터를 감지하는 Collision의 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings");
	float collisionRadius;

#pragma endregion

	// 아이템 생성 후 일정 시간이 자동 파괴(삭제)를 위한 타이머
	UPROPERTY()
	FTimerHandle destroyTimer;

public:
	// 아이템 사용자에게 효과를 적용시키는 함수
	UFUNCTION(BlueprintCallable, Category = "ItemBase")
	void UseItem(APlayerCharacter* activator) override;

	// 아이템 삭제(파괴) 함수
	void DestroyItem();

protected:
	// 아이템 주변에 다른 액터가 다가왔을 경우 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "ItemBase")
	void OnItemBeginOverlap(UPrimitiveComponent* overlapComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult) override;

};
