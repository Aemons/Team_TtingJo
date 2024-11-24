#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JHS_SkillAction.generated.h"

/**
 * SkillAction 자체는 객체화 하지 않을 클래스임
 * WeaponDataAsset에서 클래스 타입을 설정 할수 있게 할 예정
 * 직접 타격하는 종류의 스킬들과 발사체로 타격하는 스킬들의 종류가 있으므로
 * Overlap하는 함수를 자식에서 만들어서 사용
 * 부모에서 만들면 해당 함수를 사용하던 안하던 구현은 해야 하니까
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

	//Tick이 필요한 상황이 생겼을 경우 사용할 함수
	//WeaponComponent에 Tick을 연결해 놓으
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
