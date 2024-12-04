// Fill out your copyright notice in the Description page of Project Settings.


#include "YYK_PlayerCharacter.h"
#include "YYK_CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "YYK_PlayerMoveComponent.h"

// Sets default values
AYYK_PlayerCharacter::AYYK_PlayerCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UYYK_CharacterMovementComponent>(AYYK_PlayerCharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->bUsePawnControlRotation=true;

	cameraComp=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComp->SetupAttachment(springArmComp);
	cameraComp->bUsePawnControlRotation=false;

	yykMovementComp = Cast<UYYK_CharacterMovementComponent>(GetCharacterMovement());

	bUseControllerRotationYaw=true;

	playerMove=CreateDefaultSubobject<UYYK_PlayerMoveComponent>(TEXT("PlayerMoveComponent"));
}

// Called when the game starts or when spawned
void AYYK_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto pc=Cast<APlayerController>(Controller);
	if(pc)
	{
		auto subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if(subsystem)
		{
			subsystem->AddMappingContext(imc_main,0);
		}
	}
	
}

// Called every frame
void AYYK_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 플레이어 이동 처리 : 등속 운동 - P(결과 위치)=P0(현재 위치)+v(속도)*t(시간)
	direction=FTransform(GetControlRotation()).TransformVector(direction);
	AddMovementInput(direction);
	direction=FVector::ZeroVector;
}

// Called to bind functionality to input
void AYYK_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	auto playerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if(playerInput)
	{
		playerMove->SetupInputBinding(playerInput);
		
		// playerInput->BindAction(ia_Turn, ETriggerEvent::Triggered, this, &AYYK_PlayerCharacter::Turn);
		// playerInput->BindAction(ia_Lookup, ETriggerEvent::Triggered, this, &AYYK_PlayerCharacter::LookUp);
		playerInput->BindAction(ia_Move, ETriggerEvent::Triggered, this, &AYYK_PlayerCharacter::Move);
		playerInput->BindAction(ia_Jump, ETriggerEvent::Started, this, &AYYK_PlayerCharacter::InputJump);
		//playerInput->BindAction(ia_Climb, ETriggerEvent::Started, this, &AYYK_PlayerCharacter::ClimbStart);
	}
}

void AYYK_PlayerCharacter::Move(const struct FInputActionValue& inputValue)
{
	if(!yykMovementComp)	return;

	if(yykMovementComp->IsClimbing())
	{
		ClimbMove(inputValue);
	}
	else
	{
		GroundMove(inputValue);
	}
	
}

void AYYK_PlayerCharacter::GroundMove(const struct FInputActionValue& inputValue)
{
	FVector2D value = inputValue.Get<FVector2D>();
	// 상하 입력 이벤트 처리
	direction.X=value.X;
	// 좌우 입력 이벤트 처리
	direction.Y=value.Y;
}

void AYYK_PlayerCharacter::ClimbMove(const struct FInputActionValue& inputValue)
{
	FVector2D value = inputValue.Get<FVector2D>();

	FVector ForwardDirection = FVector::CrossProduct(
		-yykMovementComp->GetClimbableSurfaceNormal(),
		GetActorRightVector());

	FVector RightDirection = FVector::CrossProduct(
		-yykMovementComp->GetClimbableSurfaceNormal(),
		-GetActorUpVector());

	AddMovementInput(ForwardDirection, value.X);
	AddMovementInput(RightDirection, value.Y);
}

void AYYK_PlayerCharacter::InputJump(const struct FInputActionValue& inputValue)
{
	Jump();
}

// void AYYK_PlayerCharacter::ClimbStart(const FInputActionValue& inputValue)
// {
// 	if(!yykMovementComp) return;
// 	
// 	if(!yykMovementComp->IsClimbing())
// 	{
// 		yykMovementComp->ToggleClimbing(true);
// 	}
// 	else
// 	{
// 		yykMovementComp->ToggleClimbing(false);
// 	}
// }

//bool AYYK_PlayerCharacter::ClimbLineTracing(FHitResult& hitOut)
//{
//	FVector start=GetActorLocation();
//	FVector end=start+GetActorForwardVector()*2000.f;
//	
//	FCollisionQueryParams traceParams;
//	bool bHit = GetWorld()->LineTraceSingleByChannel(hitOut, start, end, ECC_Visibility, traceParams);
//	
//	DrawDebugLine(GetWorld(), start, end, FColor::Cyan,true,10.f);
//		
//	return bHit;
//}
