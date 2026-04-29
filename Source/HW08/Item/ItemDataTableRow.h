// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemActor.h"
#include "ItemDataTableRow.generated.h"

/**
 * 
 */
//UCLASS()
//class HW08_API UItemDataTableRow : public UObject
//{
//	GENERATED_BODY()
//	
//};

USTRUCT()
struct HW08_API FItemDataTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 아이템 고유 아이디
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGuid guid;

	// 아이템 설정을 정의한 액터 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AItemActor> itemActor;

	// 드랍율
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float probability = 0;
};