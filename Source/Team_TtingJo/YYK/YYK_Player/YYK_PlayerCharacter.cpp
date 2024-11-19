// Fill out your copyright notice in the Description page of Project Settings.


#include "YYK_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Team_TtingJo/YYK/YYK_Component/YYK_PlayerMoveComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values
AYYK_PlayerCharacter::AYYK_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	springArmComp->SetupAttachment(RootComponent);

	cameraComp=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComp->SetupAttachment(springArmComp);

	playerMove=CreateDefaultSubobject<UYYK_PlayerMoveComponent>(TEXT("PlayerMoveComponent"));
}

// Called when the game starts or when spawned
void AYYK_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYYK_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYYK_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto playerInput=CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if(playerInput)
	{
		// 컴포넌트에서 입력 바인딩 처리하도록 호출
		playerMove->SetupInputBinding(playerInput);
	}
}

