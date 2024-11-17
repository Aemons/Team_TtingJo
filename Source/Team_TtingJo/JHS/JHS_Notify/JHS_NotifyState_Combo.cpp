#include "JHS_NotifyState_Combo.h"
#include "JHS_Global.h"

#include "JHS_Component/JHS_WeaponComponent.h"
#include "JHS_Weapon/Actions/JHS_MainAction_Combo.h"
#

FString UJHS_NotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Main_Combo";
}

void UJHS_NotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_WeaponComponent* weapon = Cast<UJHS_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));
	CheckNull(weapon);
	CheckNull(weapon->GetMainAction());

	UJHS_MainAction_Combo* combo = Cast<UJHS_MainAction_Combo>(weapon->GetMainAction());
	CheckNull(combo);

	combo->EnableCombo();
}

void UJHS_NotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_WeaponComponent* weapon = Cast<UJHS_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));
	CheckNull(weapon);
	CheckNull(weapon->GetMainAction());

	UJHS_MainAction_Combo* combo = Cast<UJHS_MainAction_Combo>(weapon->GetMainAction());
	CheckNull(combo);

	combo->DisableCombo();
}
