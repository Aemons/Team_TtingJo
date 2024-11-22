#include "JHS_NotifyState_Collision.h"
#include "JHS_Global.h"

#include "JHS_Component/JHS_WeaponComponent.h"
#include "JHS_Weapon/JHS_Attachment.h"


FString UJHS_NotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UJHS_NotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_WeaponComponent* Weapon = Cast<UJHS_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));
	CheckNull(Weapon);
	CheckNull(Weapon->GetAttachment());

	Weapon->GetAttachment()->OnCollision();
}

void UJHS_NotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_WeaponComponent* Weapon = Cast<UJHS_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));
	CheckNull(Weapon);
	CheckNull(Weapon->GetAttachment());
	
	Weapon->GetAttachment()->OffCollision();
}
