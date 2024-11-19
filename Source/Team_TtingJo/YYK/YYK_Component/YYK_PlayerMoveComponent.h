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
	UPROPERTY(visibleAnywhere, Category=Component)
	TObjectPtr<UYYK_PlayerBaseComponent> playerMove;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<class UInputMappingContext> imc_TTingjo;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<class UInputAction> ia_LookUp;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<class UInputAction> ia_Turn;

public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<class UInputAction> ia_Move;

public:
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput) override;

public:
	// 좌우 회전 입력 처리
	void Turn(const struct FInputActionValue& inputValue);
	// 상하 회전 입력 처리
	void LookUp(const struct FInputActionValue& inputValue);	

	void Move(const struct FInputActionValue& inputValue);

public:
	// 이동 방향
	FVector direction;
};
