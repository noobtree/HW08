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
	
public:
	// 점수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	int32 score;

	// 현재 웨이브 종료까지의 남은 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Settings")
	int32 remainingTime;

};
