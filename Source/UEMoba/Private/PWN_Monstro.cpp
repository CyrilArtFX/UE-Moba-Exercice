#include "PWN_Monstro.h"
#include "Defines.h"
#include "GameFramework/FloatingPawnMovement.h"


APWN_Monstro::APWN_Monstro()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APWN_Monstro::BeginPlay()
{
	Super::BeginPlay();
	
	aiController = GetWorld()->SpawnActor<AAIC_Monstro>(aiControllerClass_, FTransform());
	aiController->Possess(this);
}

void APWN_Monstro::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		if (!aiController->IsMoving())
		{
			isMoving = false;
			aiController->Stop();

			FRotator rotation = GetActorRotation();
			rotation.Yaw = wantedYawRotation;
			SetActorRotation(rotation);
		}
		return;
	}
}


void APWN_Monstro::SetSpeed(float speed)
{
	kPRINT(FString::SanitizeFloat(GetMovementComponent()->GetMaxSpeed()));
}

void APWN_Monstro::SetDestination(FVector destination, float yawRotation)
{
	isMoving = aiController->SetDestination(destination);

	wantedYawRotation = yawRotation;

	if (isMoving) return;

	FRotator rotation = GetActorRotation();
	rotation.Yaw = wantedYawRotation;
	SetActorRotation(rotation);
}


