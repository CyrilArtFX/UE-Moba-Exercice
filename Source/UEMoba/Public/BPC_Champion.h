// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include <Particles/ParticleSystem.h>
#include "PWN_Monstro.h"
#include "AC_SpeedBoost.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAC_SpeedBoost* SpeedBoostComponent;


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
		float monstroSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonstroAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float monstroPingMaxDist = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonstroAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float monstroLife = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonstroAbility, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<APWN_Monstro> monstroBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonstroAbility, meta = (AllowPrivateAccess = "true"))
		UParticleSystem* monstroPingParticles;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpeedieAbility, meta = (min = 1.0f, AllowPrivateAccess = "true"))
		float speedBoost = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpeedieAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float speedBoostRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpeedieAbility, meta = (min = 0.0f, AllowPrivateAccess = "true"))
		float speedBoostDuration = 10.0f;


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


	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);


	void AbilityMonstro();
	void PingMonstro();

	void AbilitySpeed();
	
	void AbilityRecover();

	void AbilityUltimate();


protected:
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	APWN_Monstro* GetMonstro() { return monstro; }

private:
	// Cooldowns
	float monstroCrtCD = 0.0f;
	float speedieCrtCD = 0.0f;
	float recoverCrtCD = 0.0f;
	float ultiCrtCD = 0.0f;

	APWN_Monstro* monstro{ nullptr };

	FVector GetMonstroDestination();
};
