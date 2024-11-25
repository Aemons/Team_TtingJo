#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHS_WeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	//무기 추가시 Type 추가
	GreatSword, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, InNewType);

UCLASS()
class TEAM_TTINGJO_API UJHS_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()
	
public://Inline Function
	FORCEINLINE EWeaponType GetWeaponType() { return Type; }

	FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }
	FORCEINLINE bool IsGreatSword() { return Type == EWeaponType::GreatSword; }

private:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	class UJHS_WeaponDataAsset* DataAssets[(int32)EWeaponType::Max];

	UPROPERTY(EditAnywhere, Category = "WeaponChangeTime")
	float ChangeTimeOut = 5.0f;

public://Property InputAction Value
	//무기종류 추가시 InpuAction 추가
	UPROPERTY(EditAnywhere, Category = "Weapon Input")
	class UInputAction* IA_Weapon_GreatSword;

	UPROPERTY(EditAnywhere, Category = "Weapon Input")
	class UInputAction* IA_Weapon_MainAction;

	UPROPERTY(EditAnywhere, Category = "Weapon Input")
	class UInputAction* IA_Weapon_SkillAction;

//Default Function
//////////////////////////////////////////////////////////////////////////
public:	
	UJHS_WeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	virtual void InitializeComponent() override;
	void SetupInputBinding(class UEnhancedInputComponent* Input);
//////////////////////////////////////////////////////////////////////////

public://Get Weapon Classis
	class AJHS_Attachment* GetAttachment();
	class UJHS_Equipment* GetEquipment();
	class UJHS_MainAction* GetMainAction();
	class UJHS_SkillAction* GetSkillAction();

public://Set WeaponType Mode Call Function
	void SetUnarmedMode();
	void SetGreatSwordMode();

	void MainAction();

	//SkillAction Input Function
	void SkillAction_Pressed();
	void SkillAction_Relesed();

	//AttachmentClass에서 WeaponType을 설정하고 WeaponComponent에서 사용하기 위한 함수
	//일단 주먹구구식으로 만들고 나중에 인터페이스를 사용하던 델리게이트를 사용하던 구조수정해야함, 해당 함수를 Attachment에서 사용하면 지금까지 만들어놓은 구조가 망가짐
	void SetWeaponType(EWeaponType InType);
	
private:
	//현재 상태가 IdelMode 인지 확인하는 함수
	bool IsIdleMode();

private:
	//WeaponType을 비교해서 바꿔주는 함수
	void SetMode(EWeaponType InType);
	//다른 Class에 현재 WeaponType을 알려주는 함수
	void ChangeType(EWeaponType InType);

public://Delegate Value
	FWeaponTypeChanged OnWeaponTypeChanged;

private://Class Member Value
	ACharacter* OwnerCharacter;
	FTimerHandle TimeOutHandle;
	EWeaponType Type = EWeaponType::Max;
		
};
