#include "JHS_MainAction_Combo.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"
#include "JHS_Component/JHS_StateComponent.h"

void UJHS_MainAction_Combo::MainAction()
{
	CheckTrue(MainActionDatas.Num() < 1);

	if (bEnable)
	{
		bEnable = false;
		bExist = true;

		return;
	}

	CheckFalse(StateComp->IsIdleMode());

	Super::MainAction();

	MainActionDatas[Index].MainAction(OwnerCharacter);
}

void UJHS_MainAction_Combo::Begin_MainAction()
{
	Super::Begin_MainAction();

	CheckFalse(bExist);

	bExist = false;

	//Combo Count ++
	MainActionDatas[++Index].MainAction(OwnerCharacter);
}

void UJHS_MainAction_Combo::End_MainAction()
{
	Super::End_MainAction();

	//Combo Count Reset
	Index = 0;
}

void UJHS_MainAction_Combo::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCuaser, InOther);
	CheckNull(InOther);
	
	//Do not double attack
	if (HitTargets.Contains(InOther))
		return;

	HitTargets.Add(InOther);

	//TODO :: Hit data 만들면 추후 추가바람
	HitDatas[Index].SendDamage(InAttacker, InAttackCuaser, InOther);
}

void UJHS_MainAction_Combo::OnAttachmentEndCollision()
{
	Super::OnAttachmentEndCollision();

	HitTargets.Empty();
}
