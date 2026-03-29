// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceCapture.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceCapture.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceCapture.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceCapture);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	float Intelligence = 0.0f;
	GetCapturedAttributeMagnitude(IntelligenceCapture, Spec, EvaluateParams, Intelligence);
	Intelligence = FMath::Max(Intelligence, 0.0f);
	const int32 PlayerLevel = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject())->GetPlayerLevel();
	UE_LOG(LogTemp, Warning, TEXT("MaxMana = %f"), 50.0f + 2.0f * Intelligence + 5.0f * PlayerLevel);
	return 50.0f + 2.0f * Intelligence + 5.0f * PlayerLevel;
}
