// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "JHS_Component/JHS_WeaponComponent.h"

#include "Team_TtingJoCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

//WeaponComponent InputAction Delegate
DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindDelegate, class UEnhancedInputComponent*)

UCLASS(config=Game)
class ATeam_TtingJoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE EWeaponType GetPlayerWeaponType() { return WeaponType; }
	FORCEINLINE bool GetDodge() { return bIsDodge; }
	FORCEINLINE FVector2D GetMovementInput() { return MovementInputVector; }

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
public://InputAction Value
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Dodge Input Action**/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DodgeAction;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponType")
	EWeaponType WeaponType = EWeaponType::Max;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge Value")
	bool bIsDodge = false;


//Set JHS Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorComponent", meta = (DisplayPriority = "1"))
	class UJHS_WeaponComponent* WeaponComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponent", meta = (DisplayPriority = "2"))
	class UJHS_StateComponent* StateComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponent", meta = (DisplayPriority = "3"))
	class UJHS_MovemetComponent* MovementComp;
////////////////////////////////////////////////////////////////

public:
	ATeam_TtingJoCharacter();
	
protected:
	// To add mapping context
	virtual void BeginPlay();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	//Jump Function
	void OnJump();
	void OffJump();

	//Run FunctionS
	void OnRun();
	void OffRun();

	//Dodge Function
	void OnDodge();
	void OffDodge();

public:
	FInputBindDelegate OnInputBindDelegate;

private:
	bool bIsRunning = false;

	FVector2D MovementInputVector = FVector2D::ZeroVector;

	FTimerHandle DodgeHandle;
};

