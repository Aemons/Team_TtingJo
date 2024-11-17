#include "JHS_Notify_EndAction.h"
#include "JHS_Global.h"

#include "JHS_Component/JHS_WeaponComponent.h"
#include "JHS_Weapon/JHS_MainAction.h"

FString UJHS_Notify_EndAction::GetNotifyName_Implementation() const
{
	return "End_MainAction";
}

void UJHS_Notify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_WeaponComponent* weapon = Cast<UJHS_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));
	CheckNull(weapon);
	CheckNull(weapon->GetMainAction());

	weapon->GetMainAction()->End_MainAction();
}
