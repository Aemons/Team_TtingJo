#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "JHS_StateComponent.generated.h"

UENUM()
enum class EStateType : uint8
{
	Idle = 0, Equip, Hitted, Dead, MainAction, Dodge, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM_TTINGJO_API UJHS_StateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }
	FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }
	FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }
	FORCEINLINE bool IsMainActionMode() { return Type == EStateType::MainAction; }
	FORCEINLINE bool IsDodgeMode() { return Type == EStateType::Dodge; }

	//단순하게 SkillAction이냐 아니냐만 따질 것 이므로 bool변수로 만듬
	FORCEINLINE bool IsSkillActionMode() { return bIsSkillAction; }

//Default Function
public:	
	UJHS_StateComponent();

protected:
	virtual void BeginPlay() override;
///////////////////////////////////////////////////////////////////////

public://Mode Changed Function
	void SetIdleMode();
	void SetEquipMode();
	void SetHittedMode();
	void SetDeadMode();
	void SetMainActionMode();
	void SetDodgeMode();

	void OnSkillActionMode();
	void OffSkillActionMode();

private:
	void ChangeType(EStateType InType);

public:
	FStateTypeChanged OnStateTypeChanged;

private:
	EStateType Type;

private:
	bool bIsSkillAction = false;

};
