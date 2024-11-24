#pragma once

#include "CoreMinimal.h"
#include "JHS_Weapon/JHS_SkillAction.h"

#include "JHS_Weapon/JHS_WeaponStructures.h"

#include "JHS_SkillAction_Slash.generated.h"

/**
 * 부모 클래스가 Abstract 이므로 자식 클래스는 다시 Blueprintable 시켜줘야 함
 * MainAction 중에 작동이 가능한 SkillAction과 아닌 SkillAction 구분 하기
 * 위해서 MainActionMode와 SkillActionMode를 가져와서 비교해서 작동
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

	//동작이 시작할떼 일시적으로 MainAction을 때고 SkillAction을 붙혀서 실행
	void Begin_SkillAction_Implementation() override;
	//동작이 끝나면 SkillAction을 지우고 다시 MainAction을 연결
	void End_SkillAction_Implementation() override;

private:
	UFUNCTION()
	void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCuaser, class ACharacter* InOther);

	UFUNCTION()
	void OnAttachmentEndCollision();

private:
	//중복타격 방지용 객체 저장배열
	TArray<class ACharacter*> Hitted;
};
