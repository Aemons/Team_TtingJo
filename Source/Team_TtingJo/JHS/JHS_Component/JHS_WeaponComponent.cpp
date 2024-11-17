#include "JHS_WeaponComponent.h"
#include "JHS_Global.h"

#include "EnhancedInputComponent.h"

#include "JHS_Component/JHS_StateComponent.h"
#include "JHS_Weapon/JHS_WeaponDataAsset.h"
#include "JHS_Weapon/JHS_Attachment.h"
#include "JHS_Weapon/JHS_Equipment.h"
#include "JHS_Weapon/JHS_MainAction.h"

//TODO : Player 구현 후 include 수정 예정 (JHS_WeaponComponent.cpp_4)
#include "Team_TtingJo/Team_TtingJoCharacter.h"

UJHS_WeaponComponent::UJHS_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	//InitializeComponent를 사용함
	bWantsInitializeComponent = true;
}

void UJHS_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(OwnerCharacter);
	}

}

void UJHS_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJHS_WeaponComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	//TODO : Player 구현 후 Code 수정 예정 (JHS_WeaponComponent.cpp_38)
	if (ATeam_TtingJoCharacter* Player = Cast<ATeam_TtingJoCharacter>(OwnerCharacter))
	{
		Player->OnInputBindDelegate.AddUObject(this, &UJHS_WeaponComponent::SetupInputBinding);
	}
}

void UJHS_WeaponComponent::SetupInputBinding(UEnhancedInputComponent* Input)
{
	if (!!Input)
	{
		//Set WeaponMode Input
		Input->BindAction(IA_Weapon_GreatSword, ETriggerEvent::Started, this, &UJHS_WeaponComponent::SetGreatSwordMode);

		//Set MainAction Input
		Input->BindAction(IA_Weapon_MainAction, ETriggerEvent::Started, this, &UJHS_WeaponComponent::MainAction);

		//Set SkillAction Input
		Input->BindAction(IA_Weapon_SkillAction, ETriggerEvent::Started, this, &UJHS_WeaponComponent::SkillAction_Pressed);
		Input->BindAction(IA_Weapon_SkillAction, ETriggerEvent::Completed, this, &UJHS_WeaponComponent::SkillAction_Relesed);
		Input->BindAction(IA_Weapon_SkillAction, ETriggerEvent::Canceled, this, &UJHS_WeaponComponent::SkillAction_Relesed);
	}
}

//Get WeaponClass Function
AJHS_Attachment* UJHS_WeaponComponent::GetAttachment()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(!!DataAssets[(int32)Type], nullptr);

	return DataAssets[(int32)Type]->GetAttachment();
}

UJHS_Equipment* UJHS_WeaponComponent::GetEquipment()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(!!DataAssets[(int32)Type], nullptr);

	return DataAssets[(int32)Type]->GetEquipment();
}

UJHS_MainAction* UJHS_WeaponComponent::GetMainAction()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(!!DataAssets[(int32)Type], nullptr);

	return DataAssets[(int32)Type]->GetMainAction();
}
/////////////////////////////////////////////////////////////////

bool UJHS_WeaponComponent::IsIdleMode()
{
	//StateComponent의 IdleMode를 가져와서 현재 상태 check
	return Cast<UJHS_StateComponent>(OwnerCharacter->GetComponentByClass(UJHS_StateComponent::StaticClass()))->IsIdleMode();
}

void UJHS_WeaponComponent::SetUnarmedMode()
{
	CheckFalse(IsIdleMode());

	GetEquipment()->Unequip();

	ChangeType(EWeaponType::Max);
}

void UJHS_WeaponComponent::SetGreatSwordMode()
{
	CheckFalse(IsIdleMode());

	SetMode(EWeaponType::GreatSword);
}

void UJHS_WeaponComponent::MainAction()
{
	if (!!GetMainAction())
		GetMainAction()->MainAction();
}

void UJHS_WeaponComponent::SkillAction_Pressed()
{

}

void UJHS_WeaponComponent::SkillAction_Relesed()
{

}

void UJHS_WeaponComponent::SetMode(EWeaponType InType)
{
	//현재 Type과 InType이 같으면
	if (Type == InType)
	{
		//무기 장착 해제
		SetUnarmedMode();
		
		return;
	}
	else if (IsUnarmedMode() == false)
	{
		GetEquipment()->Unequip();
	}

	if (!!DataAssets[(int32)InType])
	{
		DataAssets[(int32)InType]->GetEquipment()->Equip();
		ChangeType(InType);
	}
}

void UJHS_WeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType PrevType = Type;
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(PrevType, InType);
}

