// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Team_TtingJo/YYK/YYK_Player/YYK_PlayerCharacter.h"
#include "YYK_PlayerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM_TTINGJO_API UYYK_PlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<AYYK_PlayerCharacter> me;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> moveComp;
	
public:	
	// Sets default values for this component's properties
	UYYK_PlayerBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput){};
};
