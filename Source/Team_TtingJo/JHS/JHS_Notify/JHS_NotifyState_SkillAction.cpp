#include "JHS_NotifyState_SkillAction.h"
#include "JHS_Global.h"

#include "JHS_Component/JHS_WeaponComponent.h"
#include "JHS_Weapon/JHS_SkillAction.h"

FString UJHS_NotifyState_SkillAction::GetNotifyName_Implementation() const
{
	return "SkillAction";
}

void UJHS_NotifyState_SkillAction::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	
	UJHS_WeaponComponent* Weapon = Cast<UJHS_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));
	CheckNull(Weapon);
	CheckNull(Weapon->GetSkillAction());

	Weapon->GetSkillAction()->Begin_SkillAction();
}

void UJHS_NotifyState_SkillAction::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_WeaponComponent* Weapon = Cast<UJHS_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));
	CheckNull(Weapon);
	CheckNull(Weapon->GetSkillAction());

	Weapon->GetSkillAction()->End_SkillAction();
}
