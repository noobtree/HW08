// Fill out your copyright notice in the Description page of Project Settings.


#include "FrisbeeActor.h"
#include "FPSGameState.h"

// Sets default values
AFrisbeeActor::AFrisbeeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName("SceneRootComponent"));
	SetRootComponent(defaultSceneRoot);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	meshComponent->SetupAttachment(defaultSceneRoot);

	maxHP = 3;
	currentHP = maxHP;
}

// Called when the game starts or when spawned
void AFrisbeeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFrisbeeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AFrisbeeActor::TakeDamage(float damageAmount, const FDamageEvent& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	damageAmount = Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);

	currentHP -= damageAmount;

	// 최대 또는 최소 체력 값 보장
	currentHP = FMath::Clamp(currentHP, 0, maxHP);

	// 체력이 0이면 객체 파괴
	if (currentHP == 0)
	{
		// 점수 증가
		AFPSGameState* gameState = GetWorld()->GetGameStateChecked<AFPSGameState>();
		gameState->AddScore(maxHP);
		gameState->OnTargetDestroyed();

		Destroy();
	}

	return damageAmount;
}

