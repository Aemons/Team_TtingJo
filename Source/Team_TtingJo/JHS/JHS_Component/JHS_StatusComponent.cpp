#include "JHS_StatusComponent.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"

UJHS_StatusComponent::UJHS_StatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UJHS_StatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	CurrentHealth = MaxHealth;
}

void UJHS_StatusComponent::Damage(float InAmount)
{
	CurrentHealth += (InAmount * -1.0f);
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
}
