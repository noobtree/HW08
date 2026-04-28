// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRootComponent"));
	collision = CreateDefaultSubobject<USphereComponent>(FName("SphereCollisionComponent"));
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));

	SetRootComponent(defaultSceneRoot);
	collision->SetupAttachment(defaultSceneRoot);
	meshComponent->SetupAttachment(collision);

	collisionRadius = 100;
	collision->SetSphereRadius(collisionRadius);
	collision->SetRelativeLocation(FVector(0, 0, 100));
	collision->SetCollisionProfileName(FName("OverlapAllDynamic"));
	collision->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnItemBeginOverlap);

	meshComponent->SetRelativeLocation(FVector(0, 0, -80));

	lifeTime = 5;
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	// collision 반경 설정
	collision->SetSphereRadius(collisionRadius);
	// lifeTime 이후 액터 파괴 예약
	GetWorldTimerManager().SetTimer(destroyTimer, this, &AItemActor::DestroyItem, lifeTime);
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::UseItem(APlayerCharacter* activator)
{
	// 아이템 효과 적용
	UE_LOG(LogTemp, Warning, TEXT("Trying to use Item %s"), *itemName.ToString());
	DestroyItem();
}

void AItemActor::DestroyItem()
{
	// 타이머 해제
	GetWorldTimerManager().ClearTimer(destroyTimer);
	Destroy();
}

void AItemActor::OnItemBeginOverlap(UPrimitiveComponent* overlapComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	// Overlap 이벤트를 발생시킨 액터가 플레이어 캐릭터인 경우 아이템 사용

	// 플레이어 캐릭터로 이벤트를 발생시킨 액터 변환 시도
	if (APlayerCharacter* player = Cast<APlayerCharacter>(otherActor))
	{
		// 아이템이 사용되도록 함수 호출
		UseItem(player);
		return;
	}
}
