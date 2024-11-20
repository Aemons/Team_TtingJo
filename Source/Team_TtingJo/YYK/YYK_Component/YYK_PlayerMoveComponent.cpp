// Fill out your copyright notice in the Description page of Project Settings.


#include "YYK_PlayerMoveComponent.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

void UYYK_PlayerMoveComponent::Turn(const struct FInputActionValue& inputValue)
{
	float value=inputValue.Get<float>();
	me->AddControllerYawInput(value);
}

void UYYK_PlayerMoveComponent::LookUp(const struct FInputActionValue& inputValue)
{
	float value=inputValue.Get<float>();
	me->AddControllerPitchInput(value);
}

void UYYK_PlayerMoveComponent::Move(const struct FInputActionValue& inputValue)
{
	FVector2D value=inputValue.Get<FVector2D>();
	// 상하 입력 이벤트 처리
	direction.X=value.X;
	// 좌우 입력 이벤트 처리
	direction.Y=value.Y;
}

void UYYK_PlayerMoveComponent::PlayerMove()
{
	// 플레이어 이동 처리
	direction=FTransform(me->GetControlRotation()).TransformPosition(direction);
	me->AddMovementInput(direction);
	direction=FVector::ZeroVector;
}

void UYYK_PlayerMoveComponent::SetupInputBinding(class UEnhancedInputComponent* PlayerInput)
{
	Super::SetupInputBinding(PlayerInput);
	PlayerInput->BindAction(ia_Turn, ETriggerEvent::Triggered, this, &UYYK_PlayerMoveComponent::Turn);
	PlayerInput->BindAction(ia_LookUp, ETriggerEvent::Triggered,this,&UYYK_PlayerMoveComponent::LookUp);
	PlayerInput->BindAction(ia_Move, ETriggerEvent::Triggered,this,&UYYK_PlayerMoveComponent::Move);
}
