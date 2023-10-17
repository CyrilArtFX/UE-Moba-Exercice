// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_Champion.h"
#include "BPC_Champion.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Defines.h"

void APC_Champion::BeginPlay()
{
	Super::BeginPlay();

	character = CastChecked<ABPC_Champion>(GetPawn());

	if (UEnhancedInputLocalPlayerSubsystem* input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		input_subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(character->InputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, character, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, character, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, character, &ABPC_Champion::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, character, &ABPC_Champion::Look);


		// Abilities
		EnhancedInputComponent->BindAction(monstroAction, ETriggerEvent::Triggered, character, &ABPC_Champion::AbilityMonstro);
		EnhancedInputComponent->BindAction(speedAction, ETriggerEvent::Triggered, character, &ABPC_Champion::AbilitySpeed);
		EnhancedInputComponent->BindAction(recoverAction, ETriggerEvent::Triggered, character, &ABPC_Champion::AbilityRecover);
		EnhancedInputComponent->BindAction(ultiAction, ETriggerEvent::Triggered, character, &ABPC_Champion::AbilityUltimate);
	}
}
