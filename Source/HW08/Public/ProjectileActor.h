// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

UCLASS()
class HW08_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
#pragma region Components

	// default root Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> defaultSceneRoot;

	// Capsule Collision Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> collision;

	// StaticMesh Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> meshComponent;

#pragma endregion

#pragma region General Settings

	// 발사체를 생성한 주체
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General Settings")
	TObjectPtr<AActor> attacker;

	// 발사체 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	float speed;

	// 발사체 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	float damage;

	// 발사체가 파괴되는 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	float distanceForDestroy;

	// 발사 시작점(최초 위치)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General Settings")
	FVector initialLocation;

#pragma endregion

	// 일정 주기로 최초 위치로부터의 거리를 측정하고 기준을 초과하면 액터 파괴를 관리하는 타이머
	UPROPERTY()
	FTimerHandle distanceCheckTimer;

public:
	// 발사체가 무언가와 겹쳐지거나 부딛힌 경우를 다루는 함수
	UFUNCTION()
	void OnProjectileBeginOverlap(UPrimitiveComponent* overlapComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	// 최초 위치와의 거리를 측정하고, 기준을 초과하는 경우 액터를 파괴하는 함수
	UFUNCTION()
	void CheckDistanceFromInitialLocation();

	UFUNCTION()
	void SetAttacker(AActor* newAttacker);

protected:
	void DestroyProjectile();
};
