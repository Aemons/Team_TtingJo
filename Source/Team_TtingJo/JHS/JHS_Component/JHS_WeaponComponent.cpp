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

	//TODO : 장착중인 무기를 해제한다
	bHasWeapon = false;
	
	ChangeType(EWeaponType::Max);
}

void UJHS_WeaponComponent::SetGreatSwordMode()
{
	CheckFalse(IsIdleMode());

	SetMode(EWeaponType::GreatSword);
}

void UJHS_WeaponComponent::MainAction()
{

	//무기가 장착상태가 아니면 바로 장착후 공격하기 위해
	if (Type == EWeaponType::Max)
	{
		//장착무기의 Type에 따라 Mode가 바뀌면서 장착되어야 함
		//지금 상태는 무기를 정하고 장착하는 상태임
		//SetGreatSwordMode();

		//Player에서 설정한 WeaponType을 WeponComponent의 Type으로 할당
		//할당한 Type을 바로 SetMode에 넣어줘서 Mode를 바꿈
		PlayerWeaponType(Type);
		SetMode(Type);
	}
	///////////////////////////////////////////////////

	//MainAction 실행
	if (!!GetMainAction())
	{
		GetMainAction()->MainAction();
		ResetUnarmedTimer();
	}
}

void UJHS_WeaponComponent::SkillAction_Pressed()
{
	if (!!GetSkillAction())
	{
		GetSkillAction()->Pressed();
		ResetUnarmedTimer();
	}
}

void UJHS_WeaponComponent::SkillAction_Relesed()
{
	if (!!GetSkillAction())
	{
		GetSkillAction()->Released();
		ResetUnarmedTimer();
	}
}

void UJHS_WeaponComponent::SetMode(EWeaponType InType)
{
	//Player에서 미리 WeaponType을 설정하고 SetMode에 매개변수로 넣는 방식이면 
	//기존의 방식은 Type == InType이 True이기 때문에 계속 Unarmed가 되는 상황이 생김
	//그래서 지금의 방식이면 해당 구문이 의미가 없기 때문에 주석처리 함
	//어차피 MainAction에서 WeaponTimeOut만큼의 시간이 지난후 SetUnarmedMode 호출해줌

	//현재 Type과 InType이 같으면
	/*if (Type == InType)
	{
		//무기 장착 해제
		SetUnarmedMode();
		
		return;
	}
	if (IsUnarmedMode() == false)
	{
		GetEquipment()->Unequip();
	}
	*/

	if (!!DataAssets[(int32)InType])
	{
		DataAssets[(int32)InType]->GetEquipment()->Equip();
		ChangeType(InType);
		//TODO : 무기가 장착중이다 
		bHasWeapon = true;
	}
}

void UJHS_WeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType PrevType = Type;
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(PrevType, InType);
}

void UJHS_WeaponComponent::PlayerWeaponType(EWeaponType InType)
{
	if (ATeam_TtingJoCharacter* Player = Cast<ATeam_TtingJoCharacter>(OwnerCharacter))
	{
		Type = Player->GetPlayerWeaponType();
	}
}

//Timer Function
//////////////////////////////////////////////////////////////////////
void UJHS_WeaponComponent::ResetUnarmedTimer()
{
	//함수 호출시 시간 초기화
	GetWorld()->GetTimerManager().ClearTimer(TimeOutHandle);
	//초기화와 동시에 Timer 진행
	GetWorld()->GetTimerManager().SetTimer(TimeOutHandle, this, &UJHS_WeaponComponent::SetUnarmedMode, ChangeTimeOut, false);
}
////////////////////////////////////////////////////////////////////////////

