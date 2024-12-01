// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "YYK_CharacterMovementComponent.generated.h"

/**
 * 
 */
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
#pragma endregion

#pragma region OverrideFunctions
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
#pragma endregion
public:
	void ToggleClimbing(bool bEnableClimb);
	bool IsClimbing() const;

private:
#pragma region ClimbCoreVariables
	TArray<FHitResult> climbableSurfacesTraceResults;
#pragma endregion
};
