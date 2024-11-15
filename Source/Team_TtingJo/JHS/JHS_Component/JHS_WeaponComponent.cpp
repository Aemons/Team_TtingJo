#include "JHS_WeaponComponent.h"
#include "JHS_Global.h"

#include "EnhancedInputComponent.h"

//TODO : Player ���� �� include ���� ���� (JHS_WeaponComponent.cpp_4)
#include "Team_TtingJo/Team_TtingJoCharacter.h"

UJHS_WeaponComponent::UJHS_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	//InitializeComponent�� �����
	bWantsInitializeComponent = true;
}


void UJHS_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

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

	//TODO : Player ���� �� Code ���� ���� (JHS_WeaponComponent.cpp_38)
	if (ATeam_TtingJoCharacter* Player = Cast<ATeam_TtingJoCharacter>(OwnerCharacter))
	{
		Player->OnInputBindDelegate.AddUObject(this, &UJHS_WeaponComponent::SetupInputBinding);
	}
}

void UJHS_WeaponComponent::SetupInputBinding(UEnhancedInputComponent* Input)
{
	if (!!Input)
	{
		Input->BindAction(IA_Weapon_GreatSword, ETriggerEvent::Started, this, &UJHS_WeaponComponent::SetGreatSwordMode);
	}
}

AJHS_Attachment* UJHS_WeaponComponent::GetAttachment()
{
	return nullptr;
}

void UJHS_WeaponComponent::SetUnarmedMode()
{
}

void UJHS_WeaponComponent::SetGreatSwordMode()
{
}

void UJHS_WeaponComponent::MainAction()
{
}

void UJHS_WeaponComponent::SetMode(EWeaponType InType)
{
	//���� Type�� InType�� ������
	if (Type == InType)
	{
		//���� ���� ����
		SetUnarmedMode();
		
		return;
	}
	else if (true)
	{

	}
}

void UJHS_WeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType PrevType = Type;
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(PrevType, InType);
}

