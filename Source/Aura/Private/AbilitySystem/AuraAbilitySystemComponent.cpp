// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec,
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	// GEngine->AddOnScreenDebugMessage(1, 8.0f, FColor::Blue, FString("Effect applied!"));
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);


	EffectAssetTags.Broadcast(TagContainer);
	

	
	
}
