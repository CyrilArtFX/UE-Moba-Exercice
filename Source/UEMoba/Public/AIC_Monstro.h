// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_Monstro.generated.h"

/**
 * 
 */
UCLASS()
class UEMOBA_API AAIC_Monstro : public AAIController
{
	GENERATED_BODY()
	
public:
	bool SetDestination(FVector destination);
	bool IsMoving();
	void Stop();

protected:
	void OnPossess(APawn* pawn) override;
};
