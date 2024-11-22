#include "JHS_MainAction.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"

#include "JHS_Component/JHS_StateComponent.h"
#include "JHS_Component/JHS_MovemetComponent.h"

#include "JHS_Attachment.h"
#include "JHS_Equipment.h"

UJHS_MainAction::UJHS_MainAction()
{
}

void UJHS_MainAction::BeginPlay(AJHS_Attachment* InAttachment, UJHS_Equipment* InEquipment, ACharacter* InOwner, const TArray<FMainActionData>& InMainActionData, const TArray<FHitData>& InHitData)
{
	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();

	StateComp = Cast<UJHS_StateComponent>(OwnerCharacter->GetComponentByClass(UJHS_StateComponent::StaticClass()));
	MovementComp = Cast<UJHS_MovemetComponent>(OwnerCharacter->GetComponentByClass(UJHS_MovemetComponent::StaticClass()));

	MainActionDatas = InMainActionData;
	HitDatas = InHitData;
}

void UJHS_MainAction::MainAction()
{
	bInAction = true;
	StateComp->SetMainActionMode();
}

void UJHS_MainAction::Begin_MainAction()
{
	bBeginAction = true;
}

void UJHS_MainAction::End_MainAction()
{
	bInAction = false;
	bBeginAction = false;

	MovementComp->Move();
	StateComp->SetIdleMode();
	
}
