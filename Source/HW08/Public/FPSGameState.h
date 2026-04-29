// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class HW08_API AFPSGameState : public AGameState
{
	GENERATED_BODY()

public:
	AFPSGameState();

	virtual void BeginPlay() override;
	
protected:
	// 현재 레벨에서 감지된 Spawn을 담당하는 액터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	TObjectPtr<class ASpawnVolume> spawnVolume;

#pragma region Level Settings

	// 현재 레벨의 번호
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Level Settings")
	int32 currentLevelIndex;

	// 순서대로 설정한 레벨 이름들의 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Level Settings")
	TArray<FName> levelNames;

#pragma endregion

#pragma region Wave Settings

	// 웨이브마다 생성되는 아이템 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Wave Settings")
	int32 itemCountPerWave;

	// 웨이브마다 생성되는 목표물 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Wave Settings")
	int32 targetCountPerWave;

	// 현재 월드에 생성되어있는 목표물 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "General|Wave Settings")
	int32 currentTargetCount;

	// 현재 웨이브 번호
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Wave Settings")
	int32 currentWaveIndex;

	// 레벨 마다 할당된 웨이브 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Wave Settings")
	int32 maxWavePerLevel;

	// 현재 웨이브 종료까지의 남은 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Wave Settings")
	float waveDuration;

	// 각 웨이브 시간을 관리하는 타이머
	UPROPERTY()
	FTimerHandle waveTimer;
	// UI 업데이트 주기 관리 타이머
	UPROPERTY()
	FTimerHandle uiUpdateTimer;

#pragma endregion

public:
	UFUNCTION()
	void AddScore(int32 value);

	// 목표물이 삭제되었을 경우
	UFUNCTION()
	void OnTargetDestroyed();

	void UpdateHUDWidget();

protected:
	// 레벨 시작
	UFUNCTION()
	void OnBeginLevel();

	// 웨이브 시작
	UFUNCTION()
	void OnBeginWave();

	// 웨이브 종료
	UFUNCTION()
	void OnEndWave();

	// 레벨 종료
	UFUNCTION()
	void OnEndLevel();

	// 게임 종료
	UFUNCTION()
	void OnGameOver();
};
