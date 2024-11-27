#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

//Attachment에서 WeaponType을 설정해주고 해당 WeaponType을 WeaponComponent에 알려주기 위해서 사용
//지금은 일단 임시로 이렇게 사용하고 추후에 리팩토링 할때 전체적으로 개편할 예정
//#include "JHS_Weapon/JHS_Attachment.h"

#include "JHS_WeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	//무기 추가시 Type 추가
	GreatSword, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, InNewType);

UCLASS()
class TEAM_TTINGJO_API UJHS_WeaponComponent 
	: public UActorComponent
{
	GENERATED_BODY()
	
public://Inline Function
	FORCEINLINE EWeaponType GetWeaponType() { return Type; }
	FORCEINLINE bool GetHasWaepon() { return bHasWeapon; }

	FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }
	FORCEINLINE bool IsGreatSword() { return Type == EWeaponType::GreatSword; }

private:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	class UJHS_WeaponDataAsset* DataAssets[(int32)EWeaponType::Max];

public:
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

private:
	//현재 상태가 IdelMode 인지 확인하는 함수
	bool IsIdleMode();

private:
	//WeaponType을 비교해서 바꿔주는 함수
	void SetMode(EWeaponType InType);
	//다른 Class에 현재 WeaponType을 알려주는 함수
	void ChangeType(EWeaponType InType);

	void PlayerWeaponType(EWeaponType InType);
	void ResetUnarmedTimer();

public://Delegate Value
	FWeaponTypeChanged OnWeaponTypeChanged;

private://Class Member Value
	ACharacter* OwnerCharacter;
	FTimerHandle TimeOutHandle;

	EWeaponType Type = EWeaponType::Max;
	bool bHasWeapon;
};
