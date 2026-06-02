// Fill out your copyright notice in the Description page of Project Settings.


#include "Grimoire/Public/MTPlayerCharacter.h"


// Sets default values
AMTPlayerCharacter::AMTPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMTPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMTPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMTPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

