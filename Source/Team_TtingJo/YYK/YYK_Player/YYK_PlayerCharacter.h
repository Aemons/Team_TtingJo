// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "YYK_PlayerCharacter.generated.h"

class UYYK_CharacterMovementComponent;

UCLASS()
class TEAM_TTINGJO_API AYYK_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class USpringArmComponent> springArmComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class UCameraComponent> cameraComp;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UYYK_CharacterMovementComponent* yykMovementComp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* imc_main;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Lookup;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Turn;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Jump;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* ia_Climb;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Dash;
	
public:
	// Sets default values for this character's properties
	AYYK_PlayerCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 좌우 회전 입력 처리
	void Turn(const struct FInputActionValue& inputValue);

	// 상하 회전 입력 처리
	void LookUp(const struct FInputActionValue& inputValue);

	void Move(const struct FInputActionValue& inputValue);

	void GroundMove(const struct FInputActionValue& inputValue);
	void ClimbMove(const struct FInputActionValue& inputValue);
	
	void InputJump(const struct FInputActionValue& inputValue);

	void ClimbStart(const struct FInputActionValue& inputValue);
	
	// void Dash(const struct FInputActionValue& inputValue);

public:
	UPROPERTY(EditDefaultsOnly, Category = PlayerSetting)
	float walkSpeed=200.f;

public:
	FVector direction;
};
