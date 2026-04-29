// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "FPSGameInstance.h"
#include "FPSController.h"
#include "SpawnVolume.h"
#include "FrisbeeActor.h"

AFPSGameState::AFPSGameState()
{
	waveDuration = 30;
}

void AFPSGameState::BeginPlay()
{
	Super::BeginPlay();
	
	OnBeginLevel();
}

void AFPSGameState::AddScore(int32 value)
{
	if (UGameInstance* gameInstace = GetGameInstance())
	{
		if (UFPSGameInstance* instance = CastChecked<UFPSGameInstance>(gameInstace))
		{
			instance->AddScore(value);
		}
	}
	UpdateHUDWidget();
}

void AFPSGameState::OnTargetDestroyed()
{
	--currentTargetCount;
	if (currentTargetCount <= 0)
	{
		OnEndWave();
	}
}

void AFPSGameState::OnBeginLevel()
{
	// MainMenu 맵 또는 테스트 전용 맵이 아닌 경우 레벨 시작
	FString mapName = GetWorld()->GetMapName();
	if (mapName.Contains(TEXT("MainMenu")) == true || mapName.Contains(TEXT("Overview")) == true)
	{
		return;
	}

	if (AFPSController* controller = GetWorld()->GetFirstPlayerController<AFPSController>())
	{
		controller->SetHUDWidgetVisibility(true);
	}

	// 레벨 별 따로 관리해야하는 변수 초기화
	currentWaveIndex = 0;
	// 레벨 인덱스 증가
	if (UGameInstance* gameInstace = GetGameInstance())
	{
		if (UFPSGameInstance* instance = Cast<UFPSGameInstance>(gameInstace))
		{
			currentLevelIndex = instance->GetLevelIndex();
		}
	}

	// 액터 Spawn을 담당하는 액터 찾기
	AActor* findActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnVolume::StaticClass());

	if (findActor != nullptr)
	{
		// 찾은 액터를 ASpawnVolume으로 타입 변환
		if (ASpawnVolume* buffer = CastChecked<ASpawnVolume>(findActor))
		{
			// 찾은 액터 저장
			spawnVolume = buffer;
		}
	}

	// 디버그 메시지 출력
	FString debugMsg = FString::Printf(TEXT("Begin Level %d"), currentLevelIndex + 1);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, debugMsg);

	// UI 업데이트 반복 예약
	GetWorldTimerManager().SetTimer(uiUpdateTimer, this, &AFPSGameState::UpdateHUDWidget, 0.1f, true);

	OnBeginWave();
}

void AFPSGameState::OnBeginWave()
{
	// 레벨 별 따로 관리해야하는 변수 초기화
	currentTargetCount = 0;
	int32 spawnedItemCount = 0;
	
	// 아이템 생성
	while (spawnedItemCount < itemCountPerWave)
	{
		if (spawnVolume == nullptr)
		{
			break;
		}

		// 아이템 생성
		AActor* spawnedActor = spawnVolume->SpawnRandomItem();

		// 아이템 생성이 완료된 경우 개수 증가
		if (spawnedActor != nullptr)
		{
			++spawnedItemCount;
		}
	}

	// 목표물 생성
	while (currentTargetCount < targetCountPerWave)
	{
		if (spawnVolume == nullptr)
		{
			break;
		}

		// 아이템 생성
		AActor* spawnedActor = spawnVolume->SpawnTarget();

		// 아이템 생성이 완료된 경우 개수 증가
		if (spawnedActor != nullptr)
		{
			++currentTargetCount;
		}
	}

	// 일정 시간 이후 Wave가 종료되도록 설정
	GetWorldTimerManager().SetTimer(waveTimer, this, &AFPSGameState::OnEndWave, waveDuration, false);
	
	// 디버그 메시지 출력
	FString debugMsg = FString::Printf(TEXT("Begin Wave %d"), currentWaveIndex + 1);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, debugMsg);

	UpdateHUDWidget();
}

void AFPSGameState::OnEndWave()
{
	// 타이머 해제
	GetWorldTimerManager().ClearTimer(waveTimer);

	// 웨이브 인덱스 증가
	++currentWaveIndex;
	
	// 남은 웨이브 확인
	if (currentWaveIndex < maxWavePerLevel)
	{
		// 월드에 남아있는 목표물 액터 전체 찾기
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFrisbeeActor::StaticClass(), actors);

		// 월드에 남아있는 아이템 액터 삭제
		if (actors.Num() > 0)
		{
			for (AActor*& target : actors)
			{
				target->Destroy();
			}
		}

		// 웨이브 재시작
		OnBeginWave();
	}
	else
	{
		// 현재 레벨의 종료를 알림
		OnEndLevel();
		return;
	}
}

void AFPSGameState::OnEndLevel()
{
	++currentLevelIndex;
	// 레벨 인덱스 증가
	if (UGameInstance* gameInstace = GetGameInstance())
	{
		if (UFPSGameInstance* instance = CastChecked<UFPSGameInstance>(gameInstace))
		{
			instance->SetLevelIndex(currentLevelIndex);
		}
	}

	if (levelNames.IsValidIndex(currentLevelIndex) == true)
	{
		FName loadLevelName = levelNames[currentLevelIndex];

		// 레벨 불러오기
		UGameplayStatics::OpenLevel(GetWorld(), levelNames[currentLevelIndex]);

		return;
	}
	// 불러올 레벨이 존재하지 않으면 게임 종료
	OnGameOver();
}

void AFPSGameState::OnGameOver()
{
	if (AFPSController* controller = GetWorld()->GetFirstPlayerController<AFPSController>())
	{
		controller->SetHUDWidgetVisibility(false);
		controller->SetMenuWidgetVisibility(true);
		controller->SetPause(true);
	}
	UE_LOG(LogTemp, Warning, TEXT("!!! Game Over !!!"));
}

void AFPSGameState::UpdateHUDWidget()
{
	if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	{
		AFPSController* controller = Cast<AFPSController>(playerController);
		{
			if (UUserWidget* widget = controller->GetHUDWidget())
			{
				// 시간 표시
				if (UTextBlock* timerText = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("TimerText"))))
				{
					float remainingTime = GetWorldTimerManager().GetTimerRemaining(waveTimer);
					FString textString = FString::Printf(TEXT("Time : %.1f"), remainingTime);
					timerText->SetText(FText::FromString(textString));
				}

				// 점수 표시
				if (UTextBlock* scoreText = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("ScoreText"))))
				{
					if (UFPSGameInstance* gameInstance = GetGameInstance<UFPSGameInstance>())
					{
						FString textString = FString::Printf(TEXT("Score : %d"), gameInstance->GetScore());
						scoreText->SetText(FText::FromString(textString));
					}
				}

				// 레벨, 웨이브 표시
				if (UTextBlock* mapInfoText = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("MapInfoText"))))
				{
					FString textString = FString::Printf(TEXT("Level : %d / Wave : %d"), currentLevelIndex + 1, currentWaveIndex + 1);
					mapInfoText->SetText(FText::FromString(textString));
				}

				// 체력 표시
				if (UTextBlock* hpText = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("HPText"))))
				{
					if (APlayerCharacter* player = Cast<APlayerCharacter>(controller->GetCharacter()))
					{
						FString textString = FString::Printf(TEXT("%.0f"), player->GetCurrentHitPoint());
						hpText->SetText(FText::FromString(textString));
					}
				}
			}
		}
	}
}
