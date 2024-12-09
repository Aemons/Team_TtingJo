// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "YYK_CharacterMovementComponent.generated.h"

/**
 * 
 */
class UAnimMontage;
class UAnimInstance;
UENUM(BlueprintType)
namespace ECustomMovementType
{
	enum EMyEnum
	{
		MOVE_Climb UMETA(DisplayName="Climb Mode")
	};
}


UCLASS()
class TEAM_TTINGJO_API UYYK_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

private:
#pragma region ClimbTrace
	TArray<FHitResult> DoCapsuleTraceMultiByObject(const FVector& _start, const FVector& _end, bool bShowDebugShape=false, bool bDrawPersistentShapes=false);
	FHitResult DoLineTraceSingleByObject(const FVector& _start, const FVector& _end, bool bShowDebugShape=false, bool bDrawPersistentShapes=false);
#pragma endregion

#pragma region ClimbCore
	bool TraceClimbableSurfaces();
	FHitResult TraceFromEyeHeight(float traceDistance, float traceStartOffset=0.f);
	bool CanStartClimbing();
	void StartClimbing();
	void StopClimbing();
	void PhysClimb(float deltaTime, int32 Iterations);
	void ProcessClimbableSurfaceInfo();
	bool CheckShouldStopClimbing();
	FQuat GetClimbRotation(float deltaTime);
	void SnapMovementToClimbableSurfaces(float deltaTime);
	void PlayClimbMongtage(UAnimMontage* MontageToPlay);

	UFUNCTION()
	void OnClimbMontageEnded(UAnimMontage* Montage, bool bInterrupted);
#pragma endregion

public:
#pragma region ClimbVariables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement Climbing")
	float ClimbCapsuleTraceRadius=50.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement Climbing")
	float ClimbCapsuleTraceHalfHeight=72.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement Climbing")
	TArray<TEnumAsByte<EObjectTypeQuery>> ClimbableSurfaceTraceTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement Climbing")
	float MaxBreakClimbDeceleration=400.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement Climbing")
	float MaxClimbSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement Climbing")
	float MaxClimbAcceleration = 300.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement Climbing")
	UAnimMontage* IdleToClimbMontage;
#pragma endregion

#pragma region OverrideFunctions
public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;
#pragma endregion
public:
	void ToggleClimbing(bool bEnableClimb);
	bool IsClimbing() const;
	FORCEINLINE FVector GetClimbableSurfaceNormal() const {return CurrentClimbableSurfaceNormal;}
private:
#pragma region ClimbCoreVariables
	TArray<FHitResult> climbableSurfacesTraceResults;

	FVector CurrentClimbableSurfaceLocation;
	
	FVector CurrentClimbableSurfaceNormal;

	UPROPERTY()
	UAnimInstance* OwnigPlayerInstance;
#pragma endregion
};
