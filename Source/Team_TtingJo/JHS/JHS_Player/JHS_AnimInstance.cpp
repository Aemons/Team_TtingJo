#include "JHS_AnimInstance.h"
#include "JHS_Global.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "JHS_Component/JHS_WeaponComponent.h"

//TODO : Player만들어지면 코드 교체 예정
#include "Team_TtingJo/Team_TtingJoCharacter.h"

void UJHS_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ATeam_TtingJoCharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);

	WeaponComp = Cast<UJHS_WeaponComponent>(OwnerCharacter->GetComponentByClass(UJHS_WeaponComponent::StaticClass()));

	if (!!WeaponComp)
		WeaponComp->OnWeaponTypeChanged.AddDynamic(this, &UJHS_AnimInstance::OnWeaponTypeChanged);
}

void UJHS_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	//Player Data Function
	PlayerSpeed();
	PlayerDirection();

	//Player State Check Function
	ShouldMove();
}

void UJHS_AnimInstance::PlayerSpeed()
{
	Speed = OwnerCharacter->GetVelocity().Size2D();
}

void UJHS_AnimInstance::PlayerDirection()
{
	FRotator rotator = OwnerCharacter->GetVelocity().ToOrientationRotator();
	FRotator rotator2 = OwnerCharacter->GetControlRotation();

	FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(rotator, rotator2);
	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, delta, GetDeltaSeconds(), 25);

	Direction = PrevRotation.Yaw;
}

void UJHS_AnimInstance::ShouldMove()
{
	FVector Accel = OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration();

	if (Speed > 3.0f && Accel != FVector(0, 0, 0))
		bShouldMove = true;
	else
		bShouldMove = false;

}

void UJHS_AnimInstance::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}
