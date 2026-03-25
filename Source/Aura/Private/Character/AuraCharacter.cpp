// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"


// Sets default values
AAuraCharacter::AAuraCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitiyActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitiyActorInfo();
	
}


// Called when the game starts or when spawned
void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacter::InitAbilitiyActorInfo()
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	
	AuraPS->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPS, this);
	AbilitySystemComponent = AuraPS->GetAbilitySystemComponent();
	AttributeSet = AuraPS->GetAttributeSet();

	AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController());
	if (AuraPlayerController)
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPS, AbilitySystemComponent, AttributeSet);
		}
	}
	
	
}

