#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_SpeedBoost.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEMOBA_API UAC_SpeedBoost : public UActorComponent
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

public:	
	UAC_SpeedBoost();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TriggerSpeedBoost(float speedBoost, float duration);

	float baseSpeed{ 0.0f };
	float boostTimer{ 0.0f };

private:
	void Boost(float boostValue);
};
