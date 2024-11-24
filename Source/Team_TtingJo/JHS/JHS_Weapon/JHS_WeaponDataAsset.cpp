#include "JHS_WeaponDataAsset.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"

#include "JHS_Weapon/JHS_Attachment.h"
#include "JHS_Weapon/JHS_Equipment.h"
#include "JHS_Weapon/JHS_MainAction.h"
#include "JHS_Weapon/JHS_SkillAction.h"

UJHS_WeaponDataAsset::UJHS_WeaponDataAsset()
{
	AttachmentClass = AJHS_Attachment::StaticClass();
	EquipmentClass = UJHS_Equipment::StaticClass();

	//MainActionClass는 Abstract이기 때문에 없으면 들어가면 안됨
	//MainActionClass = UJHS_MainAction::StaticClass();
	//SkillAction  또한 없으면 사용안하는 것이므로 기본값 할당 안함
}

void UJHS_WeaponDataAsset::BeginPlay(ACharacter* InOwner)
{
	if (!!AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		Attachment = InOwner->GetWorld()->SpawnActor<AJHS_Attachment>(AttachmentClass, params);
	}

	if (!!EquipmentClass)
	{
		Equipment = NewObject<UJHS_Equipment>(this, EquipmentClass);
		Equipment->BeginPlay(InOwner, EquipmentData);

		if (!!Attachment)
		{
			Equipment->OnEquipmentBeginEquip.AddDynamic(Attachment, &AJHS_Attachment::OnBeginEquip);
			Equipment->OnEquipmentEndEquip.AddDynamic(Attachment, &AJHS_Attachment::OnEndEquip);
			Equipment->OnEquipmentUnequip.AddDynamic(Attachment, &AJHS_Attachment::OnUnequip);
		}
	}

	if (!!MainActionClass)
	{
		MainAction = NewObject<UJHS_MainAction>(this, MainActionClass);
		MainAction->BeginPlay(Attachment, Equipment, InOwner, MainActionData, HitDatas);

		if (!!Attachment)
		{
			Attachment->OnAttachmentBeginCollision.AddDynamic(MainAction, &UJHS_MainAction::OnAttachmentBeginCollision);
			Attachment->OnAttachmentEndCollision.AddDynamic(MainAction, &UJHS_MainAction::OnAttachmentEndCollision);


			Attachment->OnAttachmentBeginOverlap.AddDynamic(MainAction, &UJHS_MainAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(MainAction, &UJHS_MainAction::OnAttachmentEndOverlap);
		}

		if (!!Equipment)
		{
			Equipment->OnEquipmentBeginEquip.AddDynamic(MainAction, &UJHS_MainAction::OnBeginEquip);
			Equipment->OnEquipmentUnequip.AddDynamic(MainAction, &UJHS_MainAction::OnUnequip);
		}
	}

	if (!!SkillActionClass)
	{
		SkillAction = NewObject<UJHS_SkillAction>(this, SkillActionClass);
		SkillAction->BeginPlay(InOwner, Attachment, MainAction);
	}
}
