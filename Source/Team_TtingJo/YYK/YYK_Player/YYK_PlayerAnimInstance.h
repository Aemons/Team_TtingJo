// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "YYK_PlayerAnimInstance.generated.h"

class AYYK_PlayerCharacter;
class UYYK_CharacterMovementComponent;
/**
 * 
 */
UCLASS()
class TEAM_TTINGJO_API UYYK_PlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	AYYK_PlayerCharacter* player;

	UPROPERTY()
	UYYK_CharacterMovementComponent* yykMovementComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess=true))
	float GroundSpeed;
	void GetGroundSpeed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess=true))
	float AirSpeed;
	void GetAirSpeed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess=true))
	bool bShouldMove;
	void GetShouldMove();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess=true))
	bool bIsFalling;
	void GetIsFalling();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess=true))
	bool bIsClimbing;
	void GetIsClimbing();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Reference, meta=(AllowPrivateAccess=true))
	FVector ClimbVelocity;
	void GetClimbVelocity();
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
