#include "JHS_Weapon/SkillAction/JHS_SkillAction_Slash.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"
#include "JHS_Component/JHS_StateComponent.h"
#include "JHS_Component/JHS_MovemetComponent.h"

#include "JHS_Weapon/JHS_Attachment.h"
#include "JHS_Weapon/JHS_MainAction.h"



void UJHS_SkillAction_Slash::Pressed()
{
	//현재 다른 동작을 취하고 있다면 return
	CheckFalse(StateComp->IsIdleMode());
	//이미 SkillAction 중이면 return
	CheckTrue(StateComp->IsSkillActionMode());

	Super::Pressed();

	//SkillAction중에 다른 MainAction이 들어오면 끊기기 때문에 예외처리
	//가만히 있는 동작이 아닌 공격하는 동작이므로 MainActionMode로 바꿔줌
	StateComp->SetMainActionMode();
	StateComp->OnSkillActionMode();

	//Montage 재생 기믹은 MainAction하는 로직을 사용
	MainActionData.MainAction(OwnerCharacter);
}

void UJHS_SkillAction_Slash::Begin_SkillAction_Implementation()
{
	Super::Begin_SkillAction_Implementation();

	//기존 MainAction에 연결되어 있던 델리게이트 일시적으로 제거
	Attachment->OnAttachmentBeginOverlap.Remove(MainAction, "OnAttachmentBeginOverlap");
	Attachment->OnAttachmentEndCollision.Remove(MainAction, "OnAttachmentEndCollision");

	//SkillAction에서 사용할 함수 연결
	Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &UJHS_SkillAction_Slash::OnAttachmentBeginOverlap);
	Attachment->OnAttachmentEndCollision.AddDynamic(this, &UJHS_SkillAction_Slash::OnAttachmentEndCollision);
	///////////////////////////////////////////////////////////////
}

void UJHS_SkillAction_Slash::End_SkillAction_Implementation()
{
	Super::End_SkillAction_Implementation();

	//End일때는 다시 원상태로 돌려줌
	Attachment->OnAttachmentBeginOverlap.Remove(this, "OnAttachmentBeginOverlap");
	Attachment->OnAttachmentEndCollision.Remove(this, "OnAttachmentEndCollision");

	Attachment->OnAttachmentBeginOverlap.AddDynamic(MainAction, &UJHS_MainAction::OnAttachmentBeginOverlap);
	Attachment->OnAttachmentEndCollision.AddDynamic(MainAction, &UJHS_MainAction::OnAttachmentEndCollision);
	///////////////////////////////////////////////////////////////

	StateComp->SetIdleMode();
	StateComp->OffSkillActionMode();
}

void UJHS_SkillAction_Slash::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	//JHS_Global::PRINT("Overlap");
	CheckNull(InOther);

	//중복 타격 방지
	for (ACharacter* character : Hitted)
		CheckTrue(character == InOther);
	Hitted.AddUnique(InOther);
	///////////////////////////////////////

	//Damage 전송
	HitData.SendDamage(OwnerCharacter, InAttackCuaser, InOther);
}

void UJHS_SkillAction_Slash::OnAttachmentEndCollision()
{
	Hitted.Empty();
}
