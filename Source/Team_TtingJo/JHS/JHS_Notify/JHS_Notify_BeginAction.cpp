#include "JHS_Notify_BeginAction.h"
#include "JHS_Global.h"

#include "JHS_Component/JHS_WeaponComponent.h"
#include "JHS_Weapon/JHS_MainAction.h"

FString UJHS_Notify_BeginAction::GetNotifyName_Implementation() const
{
	return "Begin_MainAction";
}

void UJHS_Notify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_WeaponComponent* weapon = Cast<UJHS_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));
	CheckNull(weapon);
	CheckNull(weapon->GetMainAction());

	weapon->GetMainAction()->Begin_MainAction();
}
