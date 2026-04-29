// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSController.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "FPSGameInstance.h"
#include "FPSGameState.h"

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

	FString currentMapName = GetWorld()->GetMapName();
	if (currentMapName.Contains(TEXT("MainMenu")))
	{
		SetMenuWidgetVisibility(false);
		return;
	}

	//if (uiHUDWidget != nullptr)
	//{
	//	hudInstance = CreateWidget<UUserWidget>(this, uiHUDWidget);
	//	if (hudInstance != nullptr)
	//	{
	//		hudInstance->AddToViewport();
	//	}
	//}

	//if (AFPSGameState* gameState = GetWorld()->GetGameStateChecked<AFPSGameState>())
	//{
	//	gameState->UpdateHUDWidget();
	//}
}

void AFPSController::SetHUDWidgetVisibility(bool bNewIsVisibility)
{
	// 기존에 생성되어있는 UI 삭제
	if (hudInstance != nullptr)
	{
		hudInstance->RemoveFromParent();
		hudInstance = nullptr;
	}
	if (menuInstance != nullptr)
	{
		menuInstance->RemoveFromParent();
		menuInstance = nullptr;
	}

	if (bNewIsVisibility == false)
	{
		return;
	}

	if (uiHUDWidget != nullptr)
	{
		// UI 생성
		hudInstance = CreateWidget<UUserWidget>(this, uiHUDWidget);
		if (hudInstance != nullptr)
		{
			// UI 출력
			hudInstance->AddToViewport();

			// 마우스 커서를 보이도록 설정
			bShowMouseCursor = false;

			// UI 입력만 받도록 처리
			SetInputMode(FInputModeGameOnly());
		}

		if (AFPSGameState* gameState = GetWorld()->GetGameStateChecked<AFPSGameState>())
		{
			gameState->UpdateHUDWidget();
		}
	}
}

void AFPSController::SetMenuWidgetVisibility(bool bIsRestart)
{
	// 기존에 생성되어있는 UI 삭제
	if (hudInstance != nullptr)
	{
		hudInstance->RemoveFromParent();
		hudInstance = nullptr;
	}
	if (menuInstance != nullptr)
	{
		menuInstance->RemoveFromParent();
		menuInstance = nullptr;
	}

	if (uiMenuWidget != nullptr)
	{
		// UI 생성
		menuInstance = CreateWidget<UUserWidget>(this, uiMenuWidget);
		if (menuInstance != nullptr)
		{
			// UI 출력
			menuInstance->AddToViewport();

			// 마우스 커서를 보이도록 설정
			bShowMouseCursor = true;

			// UI 입력만 받도록 처리
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* startButtonText = Cast<UTextBlock>(menuInstance->GetWidgetFromName(FName("StartButtonText"))))
		{
			if (bIsRestart == true)
			{
				startButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				startButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}

		if (bIsRestart == true)
		{
			UFunction* gameoverFunction = menuInstance->FindFunction(FName("OnGameOver"));
			if (gameoverFunction != nullptr)
			{
				menuInstance->ProcessEvent(gameoverFunction, nullptr);
			}

			if (UTextBlock* scoreText = Cast<UTextBlock>(menuInstance->GetWidgetFromName(FName("ScoreText"))))
			{
				if (UFPSGameInstance* gameInstance = GetGameInstance<UFPSGameInstance>())
				{
					int32 totalScore = gameInstance->GetScore();
					FString textString = FString::Printf(TEXT("Total Score : %d"), totalScore);
					scoreText->SetText(FText::FromString(textString));
				}
			}
		}
	}
}

void AFPSController::StartGame()
{
	if (UFPSGameInstance* gameInstance = GetGameInstance<UFPSGameInstance>())
	{
		gameInstance->InitializeGameState();
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName("Lvl_1"));
	SetPause(false);
}
