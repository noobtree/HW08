// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HW08/Item/ItemActor.h"
#include "PlayerCharacter.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRootComponent"));
	collision = CreateDefaultSubobject<UCapsuleComponent>(FName("CapsuleCollisionComponent"));
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	
	SetRootComponent(defaultSceneRoot);
	collision->SetupAttachment(RootComponent);
	meshComponent->SetupAttachment(collision);
	
	collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileActor::OnProjectileBeginOverlap);

	damage = 45;	// 450 J 참고
	speed = 3400;	// 340 m/s
	distanceForDestroy = 10000;	// 1000 m
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	// 초기 위치 저장
	initialLocation = GetActorLocation();
	
	// 1초마다 거리 확인 함수 호출
	GetWorldTimerManager().SetTimer(distanceCheckTimer, this, &AProjectileActor::CheckDistanceFromInitialLocation, 1, true, 3);
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 액터의 정면 방향으로 일정한 속도로 이동
	FVector deltaLocation = speed * DeltaTime * FVector::ForwardVector;
	AddActorLocalOffset(deltaLocation, true);
}

void AProjectileActor::OnProjectileBeginOverlap(UPrimitiveComponent* overlapComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	// 부딛힌 액터가 존재하지 않는 경우 함수 종료
	// 발사체를 생성한 엑터와 부딛힌 경우 함수 종료
	if (otherActor == nullptr || otherActor == this || otherActor == GetOwner())
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, otherActor->GetName());
	
	// 체력이 존재하는 액터와 부딛힌 경우
	if (otherActor->GetClass()->ImplementsInterface(UHasHitPoint::StaticClass()) == true)
	{
		// 데미지 적용
		UGameplayStatics::ApplyDamage(otherActor, damage, GetInstigatorController<AController>(), this, NULL);
	
		// 발사체 삭제
		DestroyProjectile();
		return;
	}

	// 부딛힌 액터가 아이템은 경우
	if (AItemActor* item = Cast<AItemActor>(otherActor))
	{
		// 공격자가 플레이어인지 확인
		if (APlayerCharacter* playerAttacker = Cast<APlayerCharacter>(attacker))
		{
			// 아이템 효과 적용
			item->UseItem(playerAttacker);

			// 발사체 삭제
			DestroyProjectile();
			return;
		}
	}

	
	// 맵을 구성하는 Static액터와 부딛힌 경우
	//if (otherComponent != nullptr && otherComponent->GetCollisionProfileName().IsEqual(FName("Static")) == true)
	if (otherComponent != nullptr && otherComponent->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Static? Actor"));
		// 발사체 삭제
		DestroyProjectile();
		return;
	}
}

void AProjectileActor::CheckDistanceFromInitialLocation()
{
	// 액터의 현재 위치 얻기
	FVector currrentLocation = GetActorLocation();
	
	// 최초 위치로부터의 거리 측정
	double distance = FVector::Dist(initialLocation, currrentLocation);

	// 기준 초과 시 액터 파괴
	if (distance > distanceForDestroy)
	{
		// 액터 파괴
		DestroyProjectile();
	}
}

void AProjectileActor::SetAttacker(AActor* newAttacker)
{
	if (newAttacker != nullptr && attacker != newAttacker)
	{
		attacker = newAttacker;
	}
}

void AProjectileActor::DestroyProjectile()
{
	//DrawDebugLine(GetWorld(), initialLocation, GetActorLocation(), FColor::Red, false, 5.0f, 0, 3);
	// 거리 확인 타이머 해제
	GetWorldTimerManager().ClearTimer(distanceCheckTimer);
	Destroy();
}
