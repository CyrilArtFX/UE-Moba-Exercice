#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIC_Monstro.h"
#include "PWN_Monstro.generated.h"

UCLASS()
class UEMOBA_API APWN_Monstro : public ACharacter
{
	GENERATED_BODY()

public:
	APWN_Monstro();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAIC_Monstro> aiControllerClass_;


	void SetSpeed(float speed);
	void SetLife(float life);
	void SetDestination(FVector destination, float yawRotation);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damage);

protected:
	virtual void BeginPlay() override;

private:
	AAIC_Monstro* aiController;

	float hp;
	bool isMoving{ false };

	float wantedYawRotation;
};
