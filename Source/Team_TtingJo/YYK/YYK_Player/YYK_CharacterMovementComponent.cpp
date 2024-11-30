// Fill out your copyright notice in the Description page of Project Settings.


#include "YYK_CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UYYK_CharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TraceClimbableSurfaces();
}


#pragma region ClimbTraces
TArray<FHitResult> UYYK_CharacterMovementComponent::DoCapsuleTraceMultiByObject(const FVector& _start,
	const FVector& _end, bool bShowDebugShape)
{
	TArray<FHitResult> OutCapsuleTraceHitResults;
	
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(this, _start, _end, ClimbCapsuleTraceRadius, ClimbCapsuleTraceHalfHeight
		,ClimbableSurfaceTraceTypes, false, TArray<AActor*>(),
		bShowDebugShape? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		OutCapsuleTraceHitResults,
		false
		);
	return OutCapsuleTraceHitResults;
}
#pragma endregion

#pragma region ClimbCore
void UYYK_CharacterMovementComponent::TraceClimbableSurfaces()
{
	const FVector startOffset=UpdatedComponent->GetForwardVector()*30.f;
	const FVector start=UpdatedComponent->GetComponentLocation()+startOffset;
	const FVector end=start+UpdatedComponent->GetForwardVector();
	DoCapsuleTraceMultiByObject(start,end,true);
}
#pragma endregion
