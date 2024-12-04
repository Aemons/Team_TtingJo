// Fill out your copyright notice in the Description page of Project Settings.


#include "YYK_PlayerMoveComponent.h"

#include "EnhancedInputComponent.h"

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
	
}

void UYYK_PlayerMoveComponent::SetupInputBinding(class UEnhancedInputComponent* playerInput)
{
	playerInput->BindAction(ia_Turn, ETriggerEvent::Triggered, this, &UYYK_PlayerMoveComponent::Turn);
	playerInput->BindAction(ia_Lookup, ETriggerEvent::Triggered, this, &UYYK_PlayerMoveComponent::LookUp);
}
