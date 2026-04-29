// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HasHitPoint.h"
#include "FrisbeeActor.generated.h"

UCLASS()
class HW08_API AFrisbeeActor : public AActor, public IHasHitPoint
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFrisbeeActor();

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

	// Mesh 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> meshComponent;

#pragma endregion

#pragma region HitPoint

	// 현재 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitPoint")
	float currentHP;

	// 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitPoint")
	float maxHP;

#pragma endregion

public:
#pragma region HitPoint

	// 현재 체력을 반환하는 함수
	UFUNCTION(BlueprintCallable, Category = "HitPoint")
	FORCEINLINE float GetCurrentHitPoint() const override { return currentHP; }

	// 최대 체력을 반환하는 함수
	UFUNCTION(BlueprintCallable, Category = "HitPoint")
	FORCEINLINE float GetMaxHitPoint() const override { return maxHP; }

#pragma endregion

	virtual float TakeDamage(float damageAmount, const FDamageEvent& damageEvent, AController* eventInstigator, AActor* damageCauser) override;
};
