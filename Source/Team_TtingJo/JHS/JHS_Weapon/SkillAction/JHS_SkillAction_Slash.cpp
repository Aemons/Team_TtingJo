#include "JHS_Weapon/SkillAction/JHS_SkillAction_Slash.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"
#include "JHS_Component/JHS_StateComponent.h"
#include "JHS_Component/JHS_MovemetComponent.h"

#include "JHS_Weapon/JHS_Attachment.h"
#include "JHS_Weapon/JHS_MainAction.h"



void UJHS_SkillAction_Slash::Pressed()
{
	//���� �ٸ� ������ ���ϰ� �ִٸ� return
	CheckFalse(StateComp->IsIdleMode());
	//�̹� SkillAction ���̸� return
	CheckTrue(StateComp->IsSkillActionMode());

	Super::Pressed();

	//SkillAction�߿� �ٸ� MainAction�� ������ ����� ������ ����ó��
	//������ �ִ� ������ �ƴ� �����ϴ� �����̹Ƿ� MainActionMode�� �ٲ���
	StateComp->SetMainActionMode();
	StateComp->OnSkillActionMode();

	//Montage ��� ����� MainAction�ϴ� ������ ���
	MainActionData.MainAction(OwnerCharacter);
}

void UJHS_SkillAction_Slash::Begin_SkillAction_Implementation()
{
	Super::Begin_SkillAction_Implementation();

	//���� MainAction�� ����Ǿ� �ִ� ��������Ʈ �Ͻ������� ����
	Attachment->OnAttachmentBeginOverlap.Remove(MainAction, "OnAttachmentBeginOverlap");
	Attachment->OnAttachmentEndCollision.Remove(MainAction, "OnAttachmentEndCollision");

	//SkillAction���� ����� �Լ� ����
	Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &UJHS_SkillAction_Slash::OnAttachmentBeginOverlap);
	Attachment->OnAttachmentEndCollision.AddDynamic(this, &UJHS_SkillAction_Slash::OnAttachmentEndCollision);
	///////////////////////////////////////////////////////////////
}

void UJHS_SkillAction_Slash::End_SkillAction_Implementation()
{
	Super::End_SkillAction_Implementation();

	//End�϶��� �ٽ� �����·� ������
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

	//�ߺ� Ÿ�� ����
	for (ACharacter* character : Hitted)
		CheckTrue(character == InOther);
	Hitted.AddUnique(InOther);
	///////////////////////////////////////

	//Damage ����
	HitData.SendDamage(OwnerCharacter, InAttackCuaser, InOther);
}

void UJHS_SkillAction_Slash::OnAttachmentEndCollision()
{
	Hitted.Empty();
}
