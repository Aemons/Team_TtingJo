#pragma once

#include "CoreMinimal.h"
#include "JHS_Weapon/JHS_SkillAction.h"

#include "JHS_Weapon/JHS_WeaponStructures.h"

#include "JHS_SkillAction_Slash.generated.h"

/**
 * �θ� Ŭ������ Abstract �̹Ƿ� �ڽ� Ŭ������ �ٽ� Blueprintable ������� ��
 * MainAction �߿� �۵��� ������ SkillAction�� �ƴ� SkillAction ���� �ϱ�
 * ���ؼ� MainActionMode�� SkillActionMode�� �����ͼ� ���ؼ� �۵�
 */
UCLASS(Blueprintable)
class TEAM_TTINGJO_API UJHS_SkillAction_Slash : public UJHS_SkillAction
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Action")
	FMainActionData MainActionData;

	UPROPERTY(EditAnywhere, Category = "Action")
	FHitData HitData;

public:
	void Pressed() override;

	//������ �����Ҷ� �Ͻ������� MainAction�� ���� SkillAction�� ������ ����
	void Begin_SkillAction_Implementation() override;
	//������ ������ SkillAction�� ����� �ٽ� MainAction�� ����
	void End_SkillAction_Implementation() override;

private:
	UFUNCTION()
	void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCuaser, class ACharacter* InOther);

	UFUNCTION()
	void OnAttachmentEndCollision();

private:
	//�ߺ�Ÿ�� ������ ��ü ����迭
	TArray<class ACharacter*> Hitted;
};
