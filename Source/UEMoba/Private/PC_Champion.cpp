// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_Champion.h"
#include "BPC_Champion.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void APC_Champion::BeginPlay()
{
	Super::BeginPlay();

	character = Cast<ABPC_Champion>(GetPawn());

	if (UEnhancedInputLocalPlayerSubsystem* input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		input_subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}


void APC_Champion::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* enhanced_input_component = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhanced_input_component->BindAction(JumpAction, ETriggerEvent::Triggered, character, &ACharacter::Jump);
	}
}
