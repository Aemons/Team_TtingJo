// Fill out your copyright notice in the Description page of Project Settings.


#include "YYK_PlayerMoveComponent.h"
#include "EnhancedInputComponent.h"

void UYYK_PlayerMoveComponent::SetupInputBinding(class UEnhancedInputComponent* playerInput)
{
	playerInput->BindAction(ia_Turn, ETriggerEvent::Triggered, this, &UYYK_PlayerMoveComponent::Turn);
	playerInput->BindAction(ia_Lookup, ETriggerEvent::Triggered, this, &UYYK_PlayerMoveComponent::LookUp);
	playerInput->BindAction(ia_Move, ETriggerEvent::Triggered, this, &UYYK_PlayerMoveComponent::Move);
	playerInput->BindAction(ia_Jump, ETriggerEvent::Started, this, &UYYK_PlayerMoveComponent::InputJump);
	playerInput->BindAction(ia_Climb, ETriggerEvent::Started, this, &UYYK_PlayerMoveComponent::ClimbEnd);
}


void UYYK_PlayerMoveComponent::Turn(const struct FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	player->AddControllerYawInput(value);
}

void UYYK_PlayerMoveComponent::LookUp(const struct FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	player->AddControllerPitchInput(value);
}

void UYYK_PlayerMoveComponent::Move(const struct FInputActionValue& inputValue)
{
	if(!moveComp)	return;

	if(moveComp->IsClimbing())
	{
		ClimbMove(inputValue);
	}
	else
	{
		GroundMove(inputValue);
	}
}

void UYYK_PlayerMoveComponent::GroundMove(const struct FInputActionValue& inputValue)
{
	if(!player)	return;

	FVector2D value = inputValue.Get<FVector2D>();

	player->AddMovementInput(player->GetActorForwardVector(), value.X);
	player->AddMovementInput(player->GetActorRightVector(), value.Y);
}

void UYYK_PlayerMoveComponent::ClimbMove(const struct FInputActionValue& inputValue)
{
	if (!moveComp || !player) return; // Validate moveComp and player

	FVector2D Value = inputValue.Get<FVector2D>();

	FVector ForwardDirection = FVector::CrossProduct(
		-moveComp->GetClimbableSurfaceNormal(),
		player->GetActorRightVector());
	FVector RightDirection = FVector::CrossProduct(
		-moveComp->GetClimbableSurfaceNormal(),
		-player->GetActorUpVector());

	player->AddMovementInput(ForwardDirection, Value.X);
	player->AddMovementInput(RightDirection, Value.Y);
}


void UYYK_PlayerMoveComponent::InputJump(const struct FInputActionValue& inputValue)
{
	player->Jump();
}

void UYYK_PlayerMoveComponent::ClimbEnd(const FInputActionValue& inputValue)
{
	//if(!moveComp)	return;
	//if(moveComp->IsClimbing())
	//{
	//	moveComp->ToggleClimbing(false);
	//}
}

