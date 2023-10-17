// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Champion.generated.h"

/**
 * 
 */
UCLASS()
class UEMOBA_API APC_Champion : public APlayerController
{
	GENERATED_BODY()


	// Unused for now (should be)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;


protected:
	virtual void BeginPlay();

	virtual void SetupInputComponent() override;


private:
	class ABPC_Champion* character;
};
