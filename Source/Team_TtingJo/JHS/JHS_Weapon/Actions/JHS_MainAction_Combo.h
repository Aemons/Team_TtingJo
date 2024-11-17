#pragma once

#include "CoreMinimal.h"
#include "JHS_Weapon/JHS_MainAction.h"

#include "JHS_MainAction_Combo.generated.h"

UCLASS()
class TEAM_TTINGJO_API UJHS_MainAction_Combo : public UJHS_MainAction
{
	GENERATED_BODY()

public://Combo On/Off
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

public:
	void MainAction() override;
	void Begin_MainAction() override;
	void End_MainAction() override;

public:
	void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther) override;

	void OnAttachmentEndCollision() override;


private:
	bool bEnable;
	bool bExist;

	int32 Index;

	TArray<class ACharacter*> Hitted;

	//Avoid Double Hits
	TSet<ACharacter*> HitTargets;
};
