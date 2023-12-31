// Fill out your copyright notice in the Description page of Project Settings.


#include "BPC_Champion.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Defines.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ABPC_Champion::ABPC_Champion()
{
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());


	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	SpeedBoostComponent = CreateDefaultSubobject<UAC_SpeedBoost>(TEXT("SpeedBoost"));
}


void ABPC_Champion::BeginPlay()
{
	Super::BeginPlay();

	// Set ultimate cooldown to max at the beginning of the game
	ultiCrtCD = ultiCooldown;
}


void ABPC_Champion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Decrease cooldowns each frame
	monstroCrtCD = fmax(monstroCrtCD - DeltaTime, 0.0f);
	speedieCrtCD = fmax(speedieCrtCD - DeltaTime, 0.0f);
	recoverCrtCD = fmax(recoverCrtCD - DeltaTime, 0.0f);
	ultiCrtCD = fmax(ultiCrtCD - DeltaTime, 0.0f);


	// Decrease damage recorded time
	for (int i = 0; i < damagesRecorded.Num(); i++)
	{
		damagesRecorded[i].recordTime -= DeltaTime;
		if (damagesRecorded[i].recordTime <= 0.0f)
		{
			damagesRecorded.RemoveAt(i);
			i--;
		}
	}


	// Decrease shield timer
	if (shieldTimer > 0.0f)
	{
		kPRINT_TICK("Shield : " + FString::SanitizeFloat(shield) + "  | Remain for " + FString::SanitizeFloat(shieldTimer) + " seconds.");
		shieldTimer -= DeltaTime;
		if (shieldTimer <= 0.0f)
		{
			shield = 0.0f;
		}
	}
}

void ABPC_Champion::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ABPC_Champion::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABPC_Champion::AbilityMonstro()
{
	if (monstroCrtCD > 0.0f)
	{
		kPRINT_COLOR("Monstro ability on cooldown for " + FString::SanitizeFloat(monstroCrtCD) + " seconds.", FColor::Cyan);
		return;
	}

	if (IsValid(monstro)) //  monstro already exists
	{
		monstro->Destroy();
	}
		
	monstroCrtCD = monstroCooldown;

	kPRINT("Monstro");


	FTransform monstro_transform;
	monstro_transform.SetLocation(GetActorLocation());
	monstro_transform.SetRotation(GetActorRotation().Quaternion());

	monstro = GetWorld()->SpawnActor<APWN_Monstro>(monstroBlueprint, monstro_transform);
	monstro->SetSpeed(monstroSpeed);
	monstro->SetLife(monstroLife);
}

void ABPC_Champion::PingMonstro()
{
	if (!IsValid(monstro)) return;

	FVector monstro_dest = GetMonstroDestination();

	if (monstro_dest == FVector::ZeroVector) return;

	monstro_dest += FVector::UpVector * 15.0f;

	monstro->SetDestination(monstro_dest, GetActorRotation().Yaw);
}


void ABPC_Champion::AbilitySpeed()
{
	if (speedieCrtCD > 0.0f)
	{
		kPRINT_COLOR("Speedie ability on cooldown for " + FString::SanitizeFloat(speedieCrtCD) + " seconds.", FColor::Cyan);
		return;
	}

	speedieCrtCD = speedieCooldown;

	kPRINT("Speedie");


	TArray<FHitResult> outs;


	bool hit = GetWorld()->SweepMultiByObjectType(outs, GetActorLocation(), GetActorLocation(), FQuat(), FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(speedBoostRadius));

	if (!hit)
	{
		kPRINT_COLOR("Speedie ability found no actor (bruh).", FColor::Red);
		return;
	}

	TArray<ACharacter*> checked_chara;

	for (FHitResult out : outs)
	{
		auto chara = Cast<ACharacter>(out.GetActor());
		if (!chara->IsValidLowLevel()) continue;
		
		if (checked_chara.Contains(chara)) continue;
		checked_chara.Add(chara);
		

		auto speed_comp = chara->GetComponentByClass<UAC_SpeedBoost>();
		if (!speed_comp->IsValidLowLevel()) continue;

		speed_comp->TriggerSpeedBoost(speedBoost, speedBoostDuration);
	}
}

void ABPC_Champion::AbilityRecover()
{
	if (recoverCrtCD > 0.0f)
	{
		kPRINT_COLOR("Recover ability on cooldown for " + FString::SanitizeFloat(recoverCrtCD) + " seconds.", FColor::Cyan);
		return;
	}

	recoverCrtCD = recoverCooldown;

	kPRINT("Recover");

	float new_shield = 0.0f;
	for (auto dmg_recorded : damagesRecorded)
	{
		new_shield += dmg_recorded.damage;
	}
	damagesRecorded.Empty();
	new_shield *= recoverDmgRecovred;
	shield = new_shield;
	shieldTimer = shieldDuration;
}

void ABPC_Champion::AbilityUltimate()
{
	if (ultiCrtCD > 0.0f)
	{
		kPRINT_COLOR("Ultimate ability on cooldown for " + FString::SanitizeFloat(ultiCrtCD) + " seconds.", FColor::Cyan);
		return;
	}

	ultiCrtCD = ultiCooldown;

	kPRINT("Ultimate"); 
	

	TArray<FHitResult> outs;

	bool hit = GetWorld()->SweepMultiByObjectType(outs, GetActorLocation(), GetActorLocation(), FQuat(), FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(flashRange));

	if (!hit)
	{
		kPRINT_COLOR("Ultimate ability from character found no actor (bruh).", FColor::Red);
		return;
	}

	TArray<ACharacter*> checked_chara;

	for (FHitResult out : outs)
	{
		auto chara = Cast<ACharacter>(out.GetActor());
		if (!chara->IsValidLowLevel()) continue;

		if (chara == this) continue;

		if (checked_chara.Contains(chara)) continue;
		checked_chara.Add(chara);


		auto speed_comp = chara->GetComponentByClass<UAC_Flash>();
		if (!speed_comp->IsValidLowLevel()) continue;

		FVector flash_direction = chara->GetActorLocation() - GetActorLocation();
		flash_direction.Normalize();
		if (FVector::DotProduct(GetActorForwardVector(), flash_direction) > 0.6f && FVector::DotProduct(chara->GetActorForwardVector(), -flash_direction) > 0.6f)
		{
			speed_comp->Flash(flashDuration);
			kPRINT_COLOR("Flashed " + chara->GetName() + ". (by character)", FColor::Cyan);
		}
	}

	if (!IsValid(monstro)) return;

	outs.Empty();

	hit = GetWorld()->SweepMultiByObjectType(outs, monstro->GetActorLocation(), monstro->GetActorLocation(), FQuat(), FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(flashRange));

	if (!hit)
	{
		kPRINT_COLOR("Ultimate ability from monstro found no actor (bruh).", FColor::Red);
		return;
	}

	for (FHitResult out : outs)
	{
		auto chara = Cast<ACharacter>(out.GetActor());
		if (!chara->IsValidLowLevel()) continue;

		if (checked_chara.Contains(chara)) continue;
		checked_chara.Add(chara);


		auto speed_comp = chara->GetComponentByClass<UAC_Flash>();
		if (!speed_comp->IsValidLowLevel()) continue;

		FVector flash_direction = chara->GetActorLocation() - monstro->GetActorLocation();
		flash_direction.Normalize();
		if (FVector::DotProduct(monstro->GetActorForwardVector(), flash_direction) > 0.7f && FVector::DotProduct(chara->GetActorForwardVector(), -flash_direction) > 0.7f)
		{
			speed_comp->Flash(flashDuration);
			kPRINT_COLOR("Flashed " + chara->GetName() + ". (by monstro)", FColor::Cyan);
		}
	}
}

void ABPC_Champion::TakeDamage(float damage)
{
	if (shield - damage > 0.0f)
	{
		shield -= damage;
	}
	else
	{
		damage -= shield;
		shield = 0.0f;
		health -= damage;

		damagesRecorded.Add(DamageRecord{ damage, recoverDmgRecordTime });

		if (health <= 0.0f) OnDie();
	}
}



FVector ABPC_Champion::GetMonstroDestination()
{
	FHitResult out;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	FVector cam_pos = FirstPersonCameraComponent->GetComponentLocation();
	FVector cam_direction = FirstPersonCameraComponent->GetForwardVector();
	FVector raycast_end = cam_pos + cam_direction * monstroPingMaxDist;

	bool hit = GetWorld()->LineTraceSingleByChannel(out, cam_pos, raycast_end, ECC_Camera, params);

	if (!hit) return FVector::ZeroVector;

	if (FVector::DotProduct(out.ImpactNormal, FVector::UpVector) < 0.8f) return FVector::ZeroVector;

	FVector destination = out.ImpactPoint;

	FTransform particles_transform;
	particles_transform.SetTranslation(destination + FVector::UpVector * 70.0f);
	particles_transform.SetRotation(UKismetMathLibrary::RandomRotator().Quaternion());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), monstroPingParticles, particles_transform);


	return destination;
}