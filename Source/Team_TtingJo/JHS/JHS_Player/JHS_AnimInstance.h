#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "JHS_Component/JHS_WeaponComponent.h"

#include "JHS_AnimInstance.generated.h"

UCLASS()
class TEAM_TTINGJO_API UJHS_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponType")
	EWeaponType WeaponType = EWeaponType::Max;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerData")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerData")
	float Direction;
	
protected://Bool Value
	//Player�� �����̰� �ִ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckValue")
	bool bShouldMove;

	//Player�� �޸��� �ִ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckValue")
	bool bPlayerRun;

	//Player�� �������� �ִ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckValue")
	bool bIsFalling;

	//Player�� ȸ�Ǹ���� �Z����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckValue")
	bool bIsWeaponDodge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckValue")
	class ACharacter* OwnerCharacter;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void PlayerSpeed();
	void PlayerDirection();
	void ShouldMove();
	void Falling();
	void Dodge();

private:
	UFUNCTION()
	void OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType);

private:
	FRotator PrevRotation;
	class UJHS_WeaponComponent* WeaponComp;


};
