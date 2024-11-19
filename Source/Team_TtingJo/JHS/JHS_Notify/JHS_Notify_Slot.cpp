#include "JHS_Notify_Slot.h"
#include "JHS_Global.h"

#include "JHS_Player/JHS_AnimInstance.h"
#include "Animation/AnimMontage.h"

//Temp Notify Class


FString UJHS_Notify_Slot::GetNotifyName_Implementation() const
{
	return "Slot_Change/End_Action";
}

void UJHS_Notify_Slot::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//Set Montage Slot Change
	UJHS_AnimInstance* Anim = Cast<UJHS_AnimInstance>(MeshComp->GetAnimInstance());
	CheckNull(Anim);

	if (Anim)
	{
		// ���� ��� ���� �ִϸ��̼� ��Ÿ�� ��������
		UAnimMontage* CurrentMontage = Anim->GetCurrentActiveMontage();

		if (CurrentMontage)
		{
			FName SlotName;

			// ���� �̸� ���� ����
			switch (Type)
			{
			case ESlotType::FullBody:
				CurrentMontage->SlotAnimTracks[0].SlotName = FName("FullBody");
				SlotName = FName("FullBody");
				break;
			case ESlotType::UpperBody:
				CurrentMontage->SlotAnimTracks[0].SlotName = FName("UpperBody");
				SlotName = FName("UpperBody");
				break;
			case ESlotType::Max:
				break;
			default:
				break;
			}
			//UE_LOG(LogTemp, Log, TEXT("Montage slot name changed to: NewSlotName"));
		}
	}
	/////////////////////////////////////////////////////////////////
}
