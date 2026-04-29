// Fill out your copyright notice in the Description page of Project Settings.


#include "BombItemActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/OverlapResult.h"
#include "HasHitPoint.h"

ABombItemActor::ABombItemActor()
{
	itemName = FName("Bomb");
}

void ABombItemActor::UseItem(APlayerCharacter* activator)
{
	if (activator == nullptr)
	{
		return;
	}

	// 주변에 있는 액터에게 데미지 적용
	TArray<FOverlapResult> overlapResults;
	FVector origin = GetActorLocation();
	FQuat rotator = FQuat::Identity;
	FCollisionShape collisionShape = FCollisionShape::MakeSphere(500);
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);

	GetWorld()->OverlapMultiByChannel(overlapResults, origin, rotator, ECC_Visibility, collisionShape, queryParams);

	if (overlapResults.Num() > 0)
	{
		for (const FOverlapResult& result : overlapResults)
		{
			AActor* overlapActor = result.GetActor();
			if (overlapActor == nullptr)
			{
				continue;
			}

			if (overlapActor->GetClass()->ImplementsInterface(UHasHitPoint::StaticClass()) == true)
			{
				UGameplayStatics::ApplyDamage(overlapActor, 10, nullptr, this, UDamageType::StaticClass());
			}
		}
	}

	//GetWorld()
	DestroyItem();
}
