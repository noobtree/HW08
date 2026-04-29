// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class HW08_API AFPSController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFPSController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
#pragma region Input

	// InputMappingContext 에셋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> playerMappingContext;

	// Move 입력을 정의한 InputAction 에셋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> moveInputAction;

	// Jump 입력을 정의한 InputAction 에셋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> jumpInputAction;

	// Look 입력을 정의한 InputAction 에셋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> lookInputAction;

	// double Jump 입력을 정의한 InputAction 에셋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> doubleJumpInputAction;

	// 비행 고도 조정 입력을 정의한 InputAction 에셋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> flyInputAction;

	// 공격을 위한 InputAction 에셋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> fireInputAction;

#pragma endregion

#pragma region UserInterface

	// HUD UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserInterface")
	TSubclassOf<UUserWidget> uiHUDWidget;

	// Menu UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserInterface")
	TSubclassOf<UUserWidget> uiMenuWidget;

	// 생성된 HUD UI 인스턴스
	UPROPERTY()
	UUserWidget* hudInstance;
	// 생성된 HUD UI 인스턴스
	UPROPERTY()
	UUserWidget* menuInstance;

#pragma endregion

public:
	UFUNCTION(Blueprintpure)
	FORCEINLINE UUserWidget* GetHUDWidget() const { return hudInstance; }

	UFUNCTION(BlueprintCallable)
	void SetHUDWidgetVisibility(bool bNewIsVisibility);

	UFUNCTION(BlueprintCallable)
	void SetMenuWidgetVisibility(bool bIsRestart);

	UFUNCTION(BlueprintCallable)
	void StartGame();
};
