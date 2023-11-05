#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_Flash.generated.h"


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEMOBA_API UAC_Flash : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	UAC_Flash();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintImplementableEvent)
	void Flash(float duration);
};
