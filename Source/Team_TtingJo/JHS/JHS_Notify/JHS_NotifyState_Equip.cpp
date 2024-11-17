#include "JHS_NotifyState_Equip.h"
#include "JHS_Global.h"

#include "JHS_Component/JHS_WeaponComponent.h"
#include "JHS_Weapon/JHS_Equipment.h"

FString UJHS_NotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip_State";
}

void UJHS_NotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_WeaponComponent* weapon = Cast<UJHS_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));

	CheckNull(weapon);
	CheckNull(weapon->GetEquipment());

	weapon->GetEquipment()->Begin_Equip();
}

void UJHS_NotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_WeaponComponent* weapon = Cast<UJHS_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));

	CheckNull(weapon);
	CheckNull(weapon->GetEquipment());

	weapon->GetEquipment()->End_Equip();
}
