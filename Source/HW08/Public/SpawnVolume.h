// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW08/Item/ItemDataTableRow.h"
#include "SpawnVolume.generated.h"

UCLASS()
class HW08_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> defaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> boxComponent;

#pragma endregion

	// 아이템 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (RequiredAssetDataTags = "RowStructure=/Script/HW08.ItemDataTableRow"))
	TObjectPtr<UDataTable> itemTable;

	// 목표물 클래스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> targetActor;

public:
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnRandomItem();
	AActor* SpawnTarget();

protected:
	FVector GetRandomPointInVolume() const;
	FItemDataTableRow* GetRandomItem() const;
	AActor* SpawnActorOnRandomLocation(TSubclassOf<AActor> actorClass);
};
