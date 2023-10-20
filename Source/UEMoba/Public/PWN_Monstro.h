#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIC_Monstro.h"
#include "PWN_Monstro.generated.h"

UCLASS()
class UEMOBA_API APWN_Monstro : public APawn
{
	GENERATED_BODY()

public:
	APWN_Monstro();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAIController> aiControllerClass_;


	void SetDestination(FVector destination, float yawRotation);

protected:
	virtual void BeginPlay() override;

private:
	AAIController* aiController;

	bool isMoving{ false };

	float wantedYawRotation;
};
