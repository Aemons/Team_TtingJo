// Fill out your copyright notice in the Description page of Project Settings.


#include "YYK_PlayerBaseComponent.h"

// Sets default values for this component's properties
UYYK_PlayerBaseComponent::UYYK_PlayerBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UYYK_PlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	player=Cast<AYYK_PlayerCharacter>(GetOwner());
	if(player)
	{
		moveComp=Cast<UYYK_CharacterMovementComponent>(player->GetCharacterMovement());
	}
}


// Called every frame
void UYYK_PlayerBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
