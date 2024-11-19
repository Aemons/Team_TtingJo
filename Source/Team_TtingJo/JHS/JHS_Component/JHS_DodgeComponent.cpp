#include "JHS_DodgeComponent.h"

UJHS_DodgeComponent::UJHS_DodgeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UJHS_DodgeComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UJHS_DodgeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

