#include "JHS_MovemetComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UJHS_MovemetComponent::UJHS_MovemetComponent()
{
}

void UJHS_MovemetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UJHS_MovemetComponent::SetSpeed(ESpeedType InType)
{
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed[(int32)InType];
}

void UJHS_MovemetComponent::OnWalk()
{
	SetSpeed(ESpeedType::Walk);
}

void UJHS_MovemetComponent::OnJog()
{
	SetSpeed(ESpeedType::Jog);
}

void UJHS_MovemetComponent::OnRun()
{
	SetSpeed(ESpeedType::Run);
}

void UJHS_MovemetComponent::EnableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UJHS_MovemetComponent::DisableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

