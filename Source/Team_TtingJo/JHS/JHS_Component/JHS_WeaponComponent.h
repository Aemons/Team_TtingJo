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

public:
	void SetUnarmedMode();
	void SetGreatSwordMode();

	void MainAction();

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
