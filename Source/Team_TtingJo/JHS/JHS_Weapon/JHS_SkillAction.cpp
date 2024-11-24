#include "JHS_SkillAction.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

#include "JHS_Component/JHS_StateComponent.h"
#include "JHS_Component/JHS_MovemetComponent.h"

#include "JHS_Weapon/JHS_MainAction.h"

UJHS_SkillAction::UJHS_SkillAction()
{
}

void UJHS_SkillAction::BeginPlay(ACharacter* InOwner, AJHS_Attachment* InAttachment, UJHS_MainAction* InMainAction)
{
	OwnerCharacter = InOwner;
	Attachment = InAttachment;
	MainAction = InMainAction;

	StateComp = Cast<UJHS_StateComponent>(OwnerCharacter->GetComponentByClass(UJHS_StateComponent::StaticClass()));

	MovementComp = Cast<UJHS_MovemetComponent>(OwnerCharacter->GetComponentByClass(UJHS_MovemetComponent::StaticClass()));
}
