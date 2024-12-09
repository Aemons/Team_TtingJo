// Fill out your copyright notice in the Description page of Project Settings.


#include "YYK_PlayerAnimInstance.h"
#include "YYK_PlayerCharacter.h"
#include "YYK_CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UYYK_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	player=Cast<AYYK_PlayerCharacter>(TryGetPawnOwner());

	if(player)
	{
		yykMovementComp = player->GetYYKCharacterMovementComponent();
	}
}

void UYYK_PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!player || !yykMovementComp)	return;

	GetGroundSpeed();
	GetAirSpeed();
	GetShouldMove();
	GetIsFalling();
}

void UYYK_PlayerAnimInstance::GetGroundSpeed()
{
	GroundSpeed = UKismetMathLibrary::VSizeXY(player->GetVelocity());
}

void UYYK_PlayerAnimInstance::GetAirSpeed()
{
	AirSpeed = player->GetVelocity().Z;
}

void UYYK_PlayerAnimInstance::GetShouldMove()
{
	bShouldMove = yykMovementComp->GetCurrentAcceleration().Size()>0&&GroundSpeed>5.f&&!bIsFalling;
}

void UYYK_PlayerAnimInstance::GetIsFalling()
{
	bIsFalling = yykMovementComp->IsFalling();
}

void UYYK_PlayerAnimInstance::GetIsClimbing()
{
	
}
