#include "JHS_WeaponComponent.h"
#include "JHS_Global.h"

#include "EnhancedInputComponent.h"

#include "JHS_Component/JHS_StateComponent.h"
#include "JHS_Weapon/JHS_WeaponDataAsset.h"
#include "JHS_Weapon/JHS_Attachment.h"
#include "JHS_Weapon/JHS_Equipment.h"
#include "JHS_Weapon/JHS_MainAction.h"
#include "JHS_Weapon/JHS_SkillAction.h"

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

	if (!!GetSkillAction())
		GetSkillAction()->Tick(DeltaTime);
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
UJHS_SkillAction* UJHS_WeaponComponent::GetSkillAction()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(!!DataAssets[(int32)Type], nullptr);
	
	return DataAssets[(int32)Type]->GetSkillAction();
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
	//MainAction이 호출되면 타이머 리셋
	GetWorld()->GetTimerManager().ClearTimer(TimeOutHandle);

	JHS_Global::PRINT(("Type : %d", (int32)Type));

	//무기가 장착상태가 아니면 바로 장착후 공격하기 위해
	if (Type == EWeaponType::Max)
	{
		//장착무기의 Type에 따라 Mode가 바뀌면서 장착되어야 함
		//지금 상태는 무기를 정하고 장착하는 상태임
		SetGreatSwordMode();
		//SetMode(Type); 터짐
	}
	///////////////////////////////////////////////////

	//MainAction 실행
	if (!!GetMainAction())
		GetMainAction()->MainAction();

	//일정시간 동안 입력이 없으면 SetUnarmedMode 호출
	GetWorld()->GetTimerManager().SetTimer(TimeOutHandle, this, &UJHS_WeaponComponent::SetUnarmedMode, ChangeTimeOut, false);
}

void UJHS_WeaponComponent::SkillAction_Pressed()
{
	if (!!GetSkillAction())
		GetSkillAction()->Pressed();
}

void UJHS_WeaponComponent::SkillAction_Relesed()
{
	if (!!GetSkillAction())
		GetSkillAction()->Released();
}

void UJHS_WeaponComponent::SetWeaponType(EWeaponType InType)
{
	Type = InType;
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

