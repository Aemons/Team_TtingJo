// Fill out your copyright notice in the Description page of Project Settings.


#include "JHS/JHS_Player/JHS_Enemy/JHS_Enemy.h"

// Sets default values
AJHS_Enemy::AJHS_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJHS_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJHS_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJHS_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

