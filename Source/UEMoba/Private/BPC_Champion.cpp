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

	if (IsValid(monstro)) return; //  monstro already exists

	monstroCrtCD = monstroCooldown;

	kPRINT("Monstro");


	FTransform monstro_transform;
	monstro_transform.SetLocation(GetActorLocation());
	monstro_transform.SetRotation(GetActorRotation().Quaternion());

	monstro = GetWorld()->SpawnActor<APWN_Monstro>(monstroBlueprint, monstro_transform);
}

void ABPC_Champion::PingMonstro()
{
	if (!IsValid(monstro)) return;

	FVector monstro_dest = GetMonstroDestination();

	if (monstro_dest == FVector::ZeroVector) return;

	monstro_dest += FVector::UpVector * 5.0f;

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