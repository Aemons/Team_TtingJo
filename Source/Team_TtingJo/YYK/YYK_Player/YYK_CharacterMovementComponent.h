// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "YYK_CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_TTINGJO_API UYYK_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

private:
#pragma region ClimbTrace
	TArray<FHitResult> DoCapsuleTraceMultiByObject(const FVector& _start, const FVector& _end, bool bShowDebugShape=false);
#pragma endregion

#pragma region ClimbCore
	void TraceClimbableSurfaces();

#pragma endregion

public:
#pragma region ClimbVariables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement Climbing")
	float ClimbCapsuleTraceRadius=50.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement Climbing")
	float ClimbCapsuleTraceHalfHeight=72.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement Climbing")
	TArray<TEnumAsByte<EObjectTypeQuery>> ClimbableSurfaceTraceTypes;
#pragma endregion

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
