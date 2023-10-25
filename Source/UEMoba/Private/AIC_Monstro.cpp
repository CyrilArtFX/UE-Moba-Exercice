#include "AIC_Monstro.h"
#include "Defines.h"

bool AAIC_Monstro::SetDestination(FVector destination)
{
	EPathFollowingRequestResult::Type result;
	result = MoveToLocation(destination);

	if (result == EPathFollowingRequestResult::Type::RequestSuccessful) return true;

	kPRINT_COLOR("Monstro can't reach this destination !", FColor::Red);
	return false;
}

bool AAIC_Monstro::IsMoving()
{
	return GetMoveStatus() == EPathFollowingStatus::Moving;
}

void AAIC_Monstro::Stop()
{
	StopMovement();
}

void AAIC_Monstro::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	kPRINT(pawn->GetName());
}
