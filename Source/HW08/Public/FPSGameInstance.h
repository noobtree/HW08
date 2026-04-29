// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HW08_API UFPSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFPSGameInstance();

protected:
	// 게임 누적 점수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 score;
	// 현재 실행중인 레벨의 인덱스
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 currentLevelIndex;

public:
	// 점수 추가
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddScore(int32 value);

	UFUNCTION(BlueprintCallable, Category = "GameData")
	FORCEINLINE int32 GetScore() const { return score; }

	// 레벨 번호 증가
	UFUNCTION(BlueprintCallable, Category = "GameData")
	FORCEINLINE void SetLevelIndex(int32 value) { currentLevelIndex = value; }

	// 현재 레벨의 인덱스 번호를 반환
	UFUNCTION(BlueprintCallable, Category = "GameData")
	FORCEINLINE int32 GetLevelIndex() const { return currentLevelIndex; }

	// GameState 내부 변수 값들을 초기화하는 함수
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void InitializeGameState();
};
