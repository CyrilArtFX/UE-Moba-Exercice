// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BPC_Champion.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;

UCLASS()
class UEMOBA_API ABPC_Champion : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	// Inputs (should be in PC)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;


	// Cooldowns
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonstroAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float monstroCooldown = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpeedieAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float speedieCooldown = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RecoverAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float recoverCooldown = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ultimate, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float ultiCooldown = 0.0f;

	// Abilities
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonstroAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float monstroSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonstroAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float monstroMaxCtrlTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonstroAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float monstroLifeTime = 0.0f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpeedieAbility, meta = (min = 1.0f, AllowPrivateAccess = "true"))
		float speedBoost = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpeedieAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float speedBoostRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpeedieAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float speedBoostDuration = 0.0f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RecoverAbility, meta = (min = 1.0f, AllowPrivateAccess = "true"))
		float recoverDmgRecordTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RecoverAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float recoverDmgRecovred = 0.0f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ultimate, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float flashRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ultimate, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float flashDuration = 0.0f;




public:
	ABPC_Champion();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	// Inputs (should be in PC)
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;


	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
};
