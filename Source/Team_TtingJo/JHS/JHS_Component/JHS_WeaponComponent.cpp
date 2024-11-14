#include "JHS_WeaponComponent.h"
#include "JHS_Global.h"

UJHS_WeaponComponent::UJHS_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UJHS_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UJHS_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

