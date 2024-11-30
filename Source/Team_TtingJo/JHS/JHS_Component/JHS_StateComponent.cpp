#include "JHS_StateComponent.h"
#include "JHS_Global.h"

UJHS_StateComponent::UJHS_StateComponent()
{
}

void UJHS_StateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UJHS_StateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UJHS_StateComponent::SetEquipMode()
{
	ChangeType(EStateType::Equip);
}

void UJHS_StateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}

void UJHS_StateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}

void UJHS_StateComponent::SetMainActionMode()
{
	ChangeType(EStateType::MainAction);
}

void UJHS_StateComponent::SetDodgeMode()
{
	ChangeType(EStateType::Dodge);
}

void UJHS_StateComponent::OnSkillActionMode()
{
	bIsSkillAction = true;
}

void UJHS_StateComponent::OffSkillActionMode()
{
	bIsSkillAction = false;
}

void UJHS_StateComponent::ChangeType(EStateType InType)
{
	EStateType PrevType = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(PrevType, Type);
}

