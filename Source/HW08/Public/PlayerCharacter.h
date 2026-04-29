// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HasHitPoint.h"
#include "ProjectileActor.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class HW08_API APlayerCharacter : public ACharacter, public IHasHitPoint
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
#pragma region Components

	// 1인칭 시점의 메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> firstPersonViewMesh;

	// 1인칭 시점 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> camera;

	// 무기(권총)의 메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> pistolMesh;

	// 플레이어에게 버프, 디버프 등 적용된 효과를 관리하는 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPlayerEffectManageComponent> effectManageComponent;

#pragma endregion

	// 컨트롤러의 입력 값을 반전시키는 플래그
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bIsReversed = false;

#pragma region HitPoint

	// 현재 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitPoint")
	float currentHP;
	
	// 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitPoint")
	float maxHP;

#pragma endregion

	// 공격 시 체력을 사용하는지를 결정하는 플래그
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
	bool bUseHP = true;

	// 발사체 생성 시 소모되는 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
	float projectileValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
	TSubclassOf<AProjectileActor> projectileActor;

public:
	FORCEINLINE USkeletalMeshComponent* GetFirstPersonViewMeshComponent()const { return firstPersonViewMesh; }
	FORCEINLINE UCameraComponent* GetCameraComponent()const { return camera; }

	void SetReverseInput(bool bNewIsReversed);

	void SetUseHPForAttack(bool bNewUseHP);

protected:
#pragma region InputAction

	// move
	UFUNCTION()
	void MoveAction(const FInputActionValue& value);
	// look
	UFUNCTION()
	void LookAction(const FInputActionValue& value);
	// double jump
	UFUNCTION()
	void DoubleJumpAction();
	// fly
	UFUNCTION()
	void FlyAction(const FInputActionValue& value);
	// fire pistol
	UFUNCTION()
	void FirePistolAction();

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
