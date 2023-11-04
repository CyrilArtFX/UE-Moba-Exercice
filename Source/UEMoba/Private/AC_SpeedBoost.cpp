#include "AC_SpeedBoost.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Defines.h"

UAC_SpeedBoost::UAC_SpeedBoost()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UAC_SpeedBoost::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* owner = Cast<ACharacter>(GetOwner());
	if (owner->IsValidLowLevel())
	{
		baseSpeed = owner->GetCharacterMovement()->MaxWalkSpeed;
	}
}


void UAC_SpeedBoost::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (boostTimer <= 0.0f) return;
	boostTimer -= DeltaTime;
	
	kPRINT_TICK("Current speed boost : " + FString::SanitizeFloat(boostTimer) + " seconds remaining.");

	if (boostTimer <= 0.0f)
	{
		Boost(1.0f);
	}
}

void UAC_SpeedBoost::TriggerSpeedBoost(float speedBoost, float duration)
{
	kPRINT_COLOR("Triggered speed boost of " + FString::SanitizeFloat(speedBoost) + " for " + FString::SanitizeFloat(duration) + " seconds on actor " + GetOwner()->GetName() + ".", FColor::Green);

	boostTimer = duration;
	Boost(speedBoost);
}

void UAC_SpeedBoost::Boost(float boostValue)
{
	ACharacter* owner = Cast<ACharacter>(GetOwner());
	if (owner->IsValidLowLevel())
	{
		owner->GetCharacterMovement()->MaxWalkSpeed = baseSpeed * boostValue;
	}
}

