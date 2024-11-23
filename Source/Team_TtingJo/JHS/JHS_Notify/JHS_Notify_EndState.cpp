#include "JHS_Notify_EndState.h"
#include "JHS_Global.h"

#include "JHS_Interface/JHS_EnemyInterface.h"

FString UJHS_Notify_EndState::GetNotifyName_Implementation() const
{
	return "End_State";
}

void UJHS_Notify_EndState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	IJHS_EnemyInterface* Interface = Cast<IJHS_EnemyInterface>(MeshComp->GetOwner());
	CheckNull(Interface);

	switch (StateType)
	{
	//case EStateType::Idle:
	//	break;
	//case EStateType::Equip:
	//	break;
	case EStateType::Hitted:
		Interface->End_Hitted();
		break;
	case EStateType::Dead:
		Interface->End_Dead();
		break;
	//case EStateType::MainAction:
	//	break;
	case EStateType::Max:
		break;
	default:
		break;
	}
		
}
