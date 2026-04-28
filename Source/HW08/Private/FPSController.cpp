// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSController.h"
#include "EnhancedInputSubsystems.h"

AFPSController::AFPSController()
{
}

void AFPSController::BeginPlay()
{
	Super::BeginPlay();

	// 현재 PlayerController에 연결된 LocalPlayer 얻기
	if (ULocalPlayer* localPlayer = GetLocalPlayer())
	{
		// LocalPlayer의 UEnhancedInputLocalPlayerSubsystem 클래스 얻기
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			// 향상된 입력 시스템에 InputMappingContext 에셋 등록
			if (playerMappingContext != nullptr)
			{
				subsystem->AddMappingContext(playerMappingContext, 0);
			}
		}
	}
}
