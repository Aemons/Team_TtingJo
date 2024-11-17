#include "JHS_WeaponStructures.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "JHS_Component/JHS_StateComponent.h"


//MainAction Struct Data
void FMainActionData::MainAction(ACharacter* InOwner)
{
	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRate);
}
///////////////////////////////////////////////////////////////
