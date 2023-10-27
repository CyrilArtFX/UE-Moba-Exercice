#include "AC_SpeedBoost.h"
#include "Defines.h"

UAC_SpeedBoost::UAC_SpeedBoost()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UAC_SpeedBoost::BeginPlay()
{
	Super::BeginPlay();
	
}


void UAC_SpeedBoost::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAC_SpeedBoost::TriggerSpeedBoost(float speedBoost, float duration)
{
	kPRINT_COLOR("Triggered speed boost of " + FString::SanitizeFloat(speedBoost) + " for " + FString::SanitizeFloat(duration) + " seconds on actor " + GetOwner()->GetName() + ".", FColor::Green);
}

