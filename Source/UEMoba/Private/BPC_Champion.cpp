// Fill out your copyright notice in the Description page of Project Settings.


#include "BPC_Champion.h"

// Sets default values
ABPC_Champion::ABPC_Champion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABPC_Champion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABPC_Champion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABPC_Champion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

