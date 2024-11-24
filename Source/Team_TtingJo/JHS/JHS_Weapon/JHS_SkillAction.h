#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JHS_SkillAction.generated.h"

/**
 * SkillAction ��ü�� ��üȭ ���� ���� Ŭ������
 * WeaponDataAsset���� Ŭ���� Ÿ���� ���� �Ҽ� �ְ� �� ����
 * ���� Ÿ���ϴ� ������ ��ų��� �߻�ü�� Ÿ���ϴ� ��ų���� ������ �����Ƿ�
 * Overlap�ϴ� �Լ��� �ڽĿ��� ���� ���
 * �θ𿡼� ����� �ش� �Լ��� ����ϴ� ���ϴ� ������ �ؾ� �ϴϱ�
 */
UCLASS(Abstract)
class TEAM_TTINGJO_API UJHS_SkillAction : public UObject
{
	GENERATED_BODY()
	
public:
	UJHS_SkillAction();

public:
	virtual void BeginPlay(class ACharacter* InOwner, class AJHS_Attachment* InAttachment, class UJHS_MainAction* InMainAction);

public:
	virtual void Pressed() {}
	virtual void Released() {}

public:
	UFUNCTION(BlueprintNativeEvent)
	void Begin_SkillAction();
	virtual void Begin_SkillAction_Implementation() {};

	UFUNCTION(BlueprintNativeEvent)
	void End_SkillAction();
	virtual void End_SkillAction_Implementation() {};

	//Tick�� �ʿ��� ��Ȳ�� ������ ��� ����� �Լ�
	//WeaponComponent�� Tick�� ������ ����
	UFUNCTION(BlueprintNativeEvent)
	void Tick(float InDeltaTime);
	virtual void Tick_Implementation(float InDeltaTime) {};

protected:
	class ACharacter* OwnerCharacter;
	class AJHS_Attachment* Attachment;
	class UJHS_MainAction* MainAction;

	class UJHS_StateComponent* StateComp;
	class UJHS_MovemetComponent* MovementComp;
};
