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
	
private:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	class UJHS_WeaponDataAsset* DataAssets[(int32)EWeaponType::Max];

public://Inline Function
	FORCEINLINE EWeaponType GetWeaponType() { return Type; }

public:
	FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }
	FORCEINLINE bool UsGreatSword() { return Type == EWeaponType::GreatSword; }

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

public://Set WeaponType Mode Call Function
	void SetUnarmedMode();
	void SetGreatSwordMode();

	void MainAction();

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

public://Delegate Value
	FWeaponTypeChanged OnWeaponTypeChanged;

private://Class Member Value
	ACharacter* OwnerCharacter;
	EWeaponType Type = EWeaponType::Max;
		
};
