#include "PWN_Monstro.h"
#include "Defines.h"


APWN_Monstro::APWN_Monstro()
{

	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	mesh->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));
	mesh->SetSimulatePhysics(true);
}

void APWN_Monstro::BeginPlay()
{
	Super::BeginPlay();
	
	aiController = GetWorld()->SpawnActor<AAIController>(aiControllerClass_, FTransform());
	aiController->Possess(this);
}

void APWN_Monstro::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		if (aiController->GetMoveStatus() != EPathFollowingStatus::Moving)
		{
			isMoving = false;
			aiController->StopMovement();

			FRotator rotation = GetActorRotation();
			rotation.Yaw = wantedYawRotation;
			SetActorRotation(rotation);
		}
		return;
	}
}


void APWN_Monstro::SetDestination(FVector destination, float yawRotation)
{
	isMoving = true;
	wantedYawRotation = yawRotation;
	EPathFollowingRequestResult::Type result;
	result = aiController->MoveToLocation(destination);

	kPRINT(FString::FromInt(result));
	kPRINT(destination.ToString());

	if (result == EPathFollowingRequestResult::Type::RequestSuccessful) return;
	kPRINT_COLOR("Monstro can't reach this destination !", FColor::Red);
	isMoving = false;
}


