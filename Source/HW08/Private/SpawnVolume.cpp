// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    SetRootComponent(defaultSceneRoot);

    boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    boxComponent->SetupAttachment(defaultSceneRoot);
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* ASpawnVolume::SpawnRandomItem()
{
    if (FItemDataTableRow* row = GetRandomItem())
    {
        if (UClass* itemClass = row->itemActor.Get())
        {
            return SpawnActorOnRandomLocation(itemClass);
        }
    }
    return nullptr;
}

AActor* ASpawnVolume::SpawnTarget()
{
    if (UClass* targetClass = targetActor.Get())
    {
        return SpawnActorOnRandomLocation(targetClass);
    }
    return nullptr;
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
    FVector boxExtent = boxComponent->GetScaledBoxExtent();
    FVector originLocation = GetActorLocation();

    return originLocation + FVector(
        FMath::FRandRange(-boxExtent.X, boxExtent.X),
        FMath::FRandRange(-boxExtent.Y, boxExtent.Y),
        0
    );
}

FItemDataTableRow* ASpawnVolume::GetRandomItem() const
{
    if (itemTable == nullptr)
    {
        return nullptr;
    }

    // 모든 Row 가져오기
    TArray<FItemDataTableRow*> rows;
    static const FString ContextString(TEXT("ItemSpawnContext"));
    itemTable->GetAllRows(ContextString, rows);

    if (rows.IsEmpty() == true)
    {
        return nullptr;
    }

    // 최대 확률 계산
    float maxProbility = 0; // 초기화
    for (const FItemDataTableRow* row : rows)
    {
        if (row != nullptr)
        {
            maxProbility += row->probability;
        }
    }

    // 무작위 row 선택
    float randValue = FMath::FRandRange(0.0f, maxProbility);

    // 4) 누적 확률로 아이템 선택
    for (FItemDataTableRow* row : rows)
    {
        if (randValue <= row->probability)
        {
            return row;
        }
        else
        {
            randValue -= row->probability;
        }
    }

    return nullptr;
}

AActor* ASpawnVolume::SpawnActorOnRandomLocation(TSubclassOf<AActor> actorClass)
{
    if (actorClass == nullptr)
    {
        return nullptr;
    }

    // 아래 방향으로 Linetrace를 통하여 정확한 지형의 위치 찾기
    FVector startLocation = GetRandomPointInVolume();
    FVector endLocation = startLocation + 3000 * FVector::DownVector;
    FHitResult hitResult;
    FCollisionQueryParams queryParams;
    queryParams.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECC_Visibility, queryParams) == true)
    {
        if (hitResult.bBlockingHit == true)
        {
            // 경사도 구하기
            double dot = FVector::DotProduct(FVector::UpVector, hitResult.ImpactNormal);
            double radians = FMath::Acos(dot);
            double degrees = FMath::RadiansToDegrees(radians);

            // 캐릭터가 이동 걸을 수 있는 표면에만 생성
            if (degrees < 40)
            {
                float randYaw = FMath::RandRange(-180, 180);
                AActor* item = GetWorld()->SpawnActor<AActor>(actorClass, hitResult.ImpactPoint, FRotator(0, randYaw, 0));
                return item;
            }
        }
    }
    return nullptr;
}

