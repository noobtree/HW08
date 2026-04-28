// Fill out your copyright notice in the Description page of Project Settings.


#include "DistortionVisionEffect.h"
#include "Kismet/GameplayStatics.h"

UDistortionVisionEffect::UDistortionVisionEffect()
{
	effectName = FName("DistortionVision");
	duration = 3;
}

void UDistortionVisionEffect::ApplyPlayerEffect(AActor* target) const
{
	// PostProcessVolume 액터 찾기
	if (AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), APostProcessVolume::StaticClass()))
	{
		if (APostProcessVolume* volume = CastChecked<APostProcessVolume>(actor))
		{
			UMaterialInterface* flashMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/Alcohol/MI_DistortionVision.MI_DistortionVision"));
			FWeightedBlendable materialSetting(1.0f, flashMaterial);
			volume->Settings.WeightedBlendables.Array.Add(materialSetting);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("StunGrenade!!!!"));
		}
	}
}

void UDistortionVisionEffect::RemovePlayerEffect(AActor* target) const
{
	// PostProcessVolume 액터 찾기
	if (AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), APostProcessVolume::StaticClass()))
	{
		if (APostProcessVolume* volume = CastChecked<APostProcessVolume>(actor))
		{
			volume->Settings.WeightedBlendables.Array.RemoveAll([](const FWeightedBlendable& materialSetting)
				{
					return materialSetting.Object.GetPath() == TEXT("/Game/Materials/Alcohol/MI_DistortionVision.MI_DistortionVision");
				});
		}
	}
}
