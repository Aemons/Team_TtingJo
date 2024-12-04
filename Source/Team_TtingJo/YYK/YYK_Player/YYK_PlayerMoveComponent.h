// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YYK_PlayerBaseComponent.h"
#include "YYK_PlayerMoveComponent.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_TTINGJO_API UYYK_PlayerMoveComponent : public UYYK_PlayerBaseComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Lookup;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Turn;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Move;

public:
	// 좌우 회전 입력 처리
	void Turn(const struct FInputActionValue& inputValue);

	// 상하 회전 입력 처리
	void LookUp(const struct FInputActionValue& inputValue);

	void Move(const struct FInputActionValue& inputValue);

	virtual void SetupInputBinding(class UEnhancedInputComponent* playerInput) override;

public:
	FVector direction;
};
