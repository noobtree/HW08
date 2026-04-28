// Fill out your copyright notice in the Description page of Project Settings.


#include "StunGrenadeEffect.h"
#include "Kismet/GameplayStatics.h"

UStunGrenadeEffect::UStunGrenadeEffect()
{
	effectName = FName("StunGrenade");
	duration = 2;
}

void UStunGrenadeEffect::ApplyPlayerEffect(AActor* target) const
{
	// PostProcessVolume 액터 찾기
	if (AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), APostProcessVolume::StaticClass()))
	{
		if (APostProcessVolume* volume = CastChecked<APostProcessVolume>(actor))
		{
			UMaterialInterface* flashMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/StunGrenade/MI_Flash.MI_Flash"));
			FWeightedBlendable materialSetting(1.0f, flashMaterial);
			volume->Settings.WeightedBlendables.Array.Add(materialSetting);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("StunGrenade!!!!"));
		}
	}
}

void UStunGrenadeEffect::RemovePlayerEffect(AActor* target) const
{
	// PostProcessVolume 액터 찾기
	if (AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), APostProcessVolume::StaticClass()))
	{
		if (APostProcessVolume* volume = CastChecked<APostProcessVolume>(actor))
		{
			volume->Settings.WeightedBlendables.Array.RemoveAll([](const FWeightedBlendable& materialSetting)
				{
					return materialSetting.Object.GetPath() == TEXT("/Game/Materials/StunGrenade/MI_Flash.MI_Flash");
				});
		}
	}
}
