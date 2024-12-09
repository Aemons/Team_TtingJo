// Fill out your copyright notice in the Description page of Project Settings.


#include "YYK_CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "YYK_PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

void UYYK_CharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnigPlayerInstance = CharacterOwner->GetMesh()->GetAnimInstance();

	if(OwnigPlayerInstance)
	{
		OwnigPlayerInstance->OnMontageEnded.AddDynamic(this, &UYYK_CharacterMovementComponent::OnClimbMontageEnded);
		OwnigPlayerInstance->OnMontageBlendingOut.AddDynamic(this, &UYYK_CharacterMovementComponent::OnClimbMontageEnded);
	}
}

void UYYK_CharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// 등반 가능한 표면 감지 및 등반 상태 전환
	if (!IsClimbing() && CanStartClimbing())
	{
		ToggleClimbing(true); // 등반 시작
	}
	else if (IsClimbing() && CheckShouldStopClimbing())
	{
		ToggleClimbing(false); // 등반 종료
	}
}

void UYYK_CharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode,
	uint8 PreviousCustomMode)
{
	if(IsClimbing())
	{
		bOrientRotationToMovement=false;
		CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(48.f);
	}

	if(PreviousMovementMode==MOVE_Custom && PreviousCustomMode == ECustomMovementType::MOVE_Climb)
	{
		bOrientRotationToMovement=true;
		CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(96.f);

		const FRotator DirtyRotation = UpdatedComponent->GetComponentRotation();
		const FRotator CleanStandRotation = FRotator(0.f,DirtyRotation.Yaw,0.f);
		UpdatedComponent->SetRelativeRotation(CleanStandRotation);

		StopMovementImmediately();
	}
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
}

void UYYK_CharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	if(IsClimbing())
	{
		PhysClimb(deltaTime, Iterations);
	}
	
	Super::PhysCustom(deltaTime, Iterations);
}

float UYYK_CharacterMovementComponent::GetMaxSpeed() const
{
	if(IsClimbing())
	{
		return MaxClimbSpeed;
	}
	else
	{
		return Super::GetMaxSpeed();
	}
}

float UYYK_CharacterMovementComponent::GetMaxAcceleration() const
{
	if(IsClimbing())
	{
		return MaxClimbAcceleration;
	}
	else
	{
		return Super::GetMaxAcceleration();
	}
}

#pragma region ClimbTraces
TArray<FHitResult> UYYK_CharacterMovementComponent::DoCapsuleTraceMultiByObject(const FVector& _start,
	const FVector& _end, bool bShowDebugShape, bool bDrawPersistentShapes)
{
	TArray<FHitResult> OutCapsuleTraceHitResults;

	EDrawDebugTrace::Type debugTraceType=EDrawDebugTrace::None;

	if(bShowDebugShape)
	{
		debugTraceType=EDrawDebugTrace::ForOneFrame;

		if (bDrawPersistentShapes)
		{
			debugTraceType=EDrawDebugTrace::Persistent;
		}
	}
	
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(this,
		_start,
		_end,
		ClimbCapsuleTraceRadius,
		ClimbCapsuleTraceHalfHeight
		,ClimbableSurfaceTraceTypes,
		false,
		TArray<AActor*>(),
		debugTraceType,
		OutCapsuleTraceHitResults,
		false
		);
	return OutCapsuleTraceHitResults;
}

FHitResult UYYK_CharacterMovementComponent::DoLineTraceSingleByObject(const FVector& _start, const FVector& _end,
	bool bShowDebugShape, bool bDrawPersistentShapes)
{
	FHitResult outHit;
	
	EDrawDebugTrace::Type debugTraceType=EDrawDebugTrace::None;

	if(bShowDebugShape)
	{
		debugTraceType=EDrawDebugTrace::ForOneFrame;

		if (bDrawPersistentShapes)
		{
			debugTraceType=EDrawDebugTrace::Persistent;
		}
	}
	UKismetSystemLibrary::LineTraceSingleForObjects(
		this,
		_start,
		_end, 
		ClimbableSurfaceTraceTypes,
		false,
		TArray<AActor*>(),
		debugTraceType,
		outHit,
		false
	);

	return outHit;
}
#pragma endregion

#pragma region ClimbCore
void UYYK_CharacterMovementComponent::ToggleClimbing(bool bEnableClimb)
{
	if(bEnableClimb)
	{
		if(CanStartClimbing())
		{
			// climb state에 들어가기
			//StartClimbing();
			PlayClimbMongtage(IdleToClimbMontage);
		}
	}
	else
	{
		// 등반 멈춤
		StopClimbing();
	}
}

bool UYYK_CharacterMovementComponent::IsClimbing() const
{
	return MovementMode==MOVE_Custom && CustomMovementMode==ECustomMovementType::MOVE_Climb;
}

// trace for climbable surfaces
bool UYYK_CharacterMovementComponent::TraceClimbableSurfaces()
{
	const FVector startOffset=UpdatedComponent->GetForwardVector()*30.f;
	const FVector start=UpdatedComponent->GetComponentLocation()+startOffset;
	const FVector end=start+UpdatedComponent->GetForwardVector();
	climbableSurfacesTraceResults = DoCapsuleTraceMultiByObject(start,end);

	return !climbableSurfacesTraceResults.IsEmpty();
}

FHitResult UYYK_CharacterMovementComponent::TraceFromEyeHeight(float traceDistance, float traceStartOffset)
{
	const FVector componentLocation=UpdatedComponent->GetComponentLocation();
	const FVector eyeHeightOffset=UpdatedComponent->GetUpVector()*(CharacterOwner->BaseEyeHeight+traceStartOffset);
	const FVector start=componentLocation+eyeHeightOffset;
	const FVector end=start+UpdatedComponent->GetForwardVector()*traceDistance;

	return DoLineTraceSingleByObject(start, end);
}

bool UYYK_CharacterMovementComponent::CanStartClimbing()
{
	if(IsFalling())	return false;
	if(!TraceClimbableSurfaces())	return false;
	if(!TraceFromEyeHeight(100.f).bBlockingHit)	return false;

	return true;
}

void UYYK_CharacterMovementComponent::StartClimbing()
{
	SetMovementMode(MOVE_Custom, ECustomMovementType::MOVE_Climb);
}

void UYYK_CharacterMovementComponent::StopClimbing()
{
	SetMovementMode(MOVE_Falling);
}

void UYYK_CharacterMovementComponent::PhysClimb(float deltaTime, int32 Iterations)
{
	if (deltaTime < MIN_TICK_TIME)
	{
		return;
	}
	
	// Process all the climable surfaces info
	TraceClimbableSurfaces();
	ProcessClimbableSurfaceInfo();
	
	// check if we should stop climbing
	if(CheckShouldStopClimbing())
	{
		StopClimbing();
	}
	RestorePreAdditiveRootMotionVelocity();
	
	if( !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() )
	{
		// define the max climb speed and acceleration
		CalcVelocity(deltaTime, 0.f, true, MaxBreakClimbDeceleration);
	}

	ApplyRootMotionToVelocity(deltaTime);
	
	FVector OldLocation = UpdatedComponent->GetComponentLocation();
	const FVector Adjusted = Velocity * deltaTime;
	FHitResult Hit(1.f);
	
	// handle climb rotation
	SafeMoveUpdatedComponent(Adjusted, GetClimbRotation(deltaTime), true, Hit);

	if (Hit.Time < 1.f)
	{
		//adjust and try again
		HandleImpact(Hit, deltaTime, Adjusted);
		SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
	}

	if(!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() )
	{
		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
	}
	// snap movement to climbable surfaces
	SnapMovementToClimbableSurfaces(deltaTime);
}

void UYYK_CharacterMovementComponent::ProcessClimbableSurfaceInfo()
{
	CurrentClimbableSurfaceLocation = FVector::ZeroVector;
	CurrentClimbableSurfaceNormal = FVector::ZeroVector;

	if(climbableSurfacesTraceResults.IsEmpty())	return;

	for(const FHitResult& hitResult : climbableSurfacesTraceResults)
	{
		CurrentClimbableSurfaceLocation += hitResult.ImpactPoint;
		CurrentClimbableSurfaceNormal += hitResult.ImpactNormal;
	}
	CurrentClimbableSurfaceLocation /= climbableSurfacesTraceResults.Num();
	CurrentClimbableSurfaceNormal = CurrentClimbableSurfaceNormal.GetSafeNormal();
}

bool UYYK_CharacterMovementComponent::CheckShouldStopClimbing()
{
	if(climbableSurfacesTraceResults.IsEmpty())	return true;

	const float dotResult=FVector::DotProduct(CurrentClimbableSurfaceNormal, FVector::UpVector);
	const float degreeDiff=FMath::RadiansToDegrees(FMath::Acos(dotResult));

	if(degreeDiff<=30.f)
		return true;
	
	return false;
}

FQuat UYYK_CharacterMovementComponent::GetClimbRotation(float deltaTime)
{
	const FQuat currentQuat = UpdatedComponent->GetComponentQuat();
	if(HasAnimRootMotion() || CurrentRootMotion.HasOverrideVelocity())
	{
		return currentQuat;
	}

	const FQuat TargetQuat = FRotationMatrix::MakeFromX(-CurrentClimbableSurfaceNormal).ToQuat();
	return FMath::QInterpTo(currentQuat, TargetQuat, deltaTime,5.f);
}

void UYYK_CharacterMovementComponent::SnapMovementToClimbableSurfaces(float deltaTime)
{
	const FVector componentForward = UpdatedComponent->GetForwardVector();
	const FVector componentLocation = UpdatedComponent->GetComponentLocation();

	const FVector projectedCharacterToSurface = (CurrentClimbableSurfaceLocation - componentLocation).ProjectOnTo(componentForward);

	const FVector snapVector = -CurrentClimbableSurfaceNormal*projectedCharacterToSurface.Length();

	UpdatedComponent->MoveComponent(snapVector*deltaTime*MaxClimbSpeed,
		UpdatedComponent->GetComponentQuat(),
		true);
}

void UYYK_CharacterMovementComponent::PlayClimbMongtage(UAnimMontage* MontageToPlay)
{
	if(!MontageToPlay)	return;
	if(!OwnigPlayerInstance)	return;
	if(OwnigPlayerInstance->IsAnyMontagePlaying())	return;

	OwnigPlayerInstance->Montage_Play(MontageToPlay);
}

void UYYK_CharacterMovementComponent::OnClimbMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == IdleToClimbMontage)
	{
		StartClimbing();
	}
}

#pragma endregion
