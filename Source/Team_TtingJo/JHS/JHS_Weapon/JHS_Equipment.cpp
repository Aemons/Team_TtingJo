#include "JHS_Equipment.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"

#include "JHS_Component/JHS_StateComponent.h"
#include "JHS_Component/JHS_MovemetComponent.h"

void UJHS_Equipment::BeginPlay(ACharacter* InOwner, const FEquipmentData& InData)
{
	OwnerCharacter = InOwner;
	Data = InData;

	StateComp = Cast<UJHS_StateComponent>(OwnerCharacter->GetComponentByClass(UJHS_StateComponent::StaticClass()));
	MovementComp = Cast<UJHS_MovemetComponent>(OwnerCharacter->GetComponentByClass(UJHS_MovemetComponent::StaticClass()));
}

void UJHS_Equipment::Equip()
{
	StateComp->SetEquipMode();
	
	if (OnEquipmentEquip.IsBound())
		OnEquipmentEquip.Broadcast();
	
	if (Data.bUseControllerRotation)
		MovementComp->EnableControlRotation();

	if (!!Data.Montage && StateComp->IsMainActionMode() == false)
	{
		OwnerCharacter->PlayAnimMontage(Data.Montage, Data.PlayRate);
	}
	else
	{
		Begin_Equip();
		End_Equip();
	}
}

void UJHS_Equipment::Unequip()
{
	bEquipped = false;
	MovementComp->DisableControlRotation();

	if (OnEquipmentUnequip.IsBound())
		OnEquipmentUnequip.Broadcast();
}

void UJHS_Equipment::Begin_Equip()
{
	bBeginEquip = true;

	if (OnEquipmentBeginEquip.IsBound())
		OnEquipmentBeginEquip.Broadcast();
}

void UJHS_Equipment::End_Equip()
{
	bBeginEquip = false;
	bEquipped = true;

	StateComp->SetIdleMode();

	if (OnEquipmentEndEquip.IsBound())
		OnEquipmentEndEquip.Broadcast();
}

