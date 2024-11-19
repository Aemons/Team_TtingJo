#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "JHS_WeaponStructures.h"

#include "JHS_MainAction.generated.h"

//Weapon Attack Action Class

UCLASS(Abstract)
class TEAM_TTINGJO_API UJHS_MainAction : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE bool GetBeginAction() { return bBeginAction; }
	FORCEINLINE bool GetInAction() { return bInAction; }

//Default Function
public:
	UJHS_MainAction();

	virtual void BeginPlay
	(
		class AJHS_Attachment* InAttachment,
		class UJHS_Equipment* InEquipment,
		class ACharacter* InOwner,
		const TArray<FMainActionData>& InMainActionData
	);
//////////////////////////////////////////////////////////////////

public:
	virtual void MainAction();

	virtual void Begin_MainAction();
	virtual void End_MainAction();

public://Attachment Class Delegate Call Function
	UFUNCTION()
	virtual void OnAttachmentBeginCollision() {}

	UFUNCTION()
	virtual void OnAttachmentEndCollision() {}

	UFUNCTION()
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther) { }

	UFUNCTION()
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class ACharacter* InOther) { }

public:
	UFUNCTION()
	virtual void OnBeginEquip() { }

	UFUNCTION()
	virtual void OnUnequip() { }


protected:
	bool bBeginAction;
	bool bInAction;

	class ACharacter* OwnerCharacter;
	class UWorld* World;

	class UJHS_StateComponent* StateComp;
	class UJHS_MovemetComponent* MovementComp;

	TArray<FMainActionData> MainActionData;
	
};
