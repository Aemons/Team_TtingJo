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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerData")
	float ForwardInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerData")
	float RightInput;

protected://Bool Value
	//Player가 움직이고 있는지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckValue")
	bool bShouldMove;

	//Player가 달리고 있는지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckValue")
	bool bPlayerRun;

	//Player가 떨어지고 있는지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckValue")
	bool bIsFalling;

	//Player가 회피명령을 줫는지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckValue")
	bool bIsDodge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckValue")
	//class ACharacter* OwnerCharacter;
	class ATeam_TtingJoCharacter* OwnerCharacter;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void PlayerSpeed();
	void PlayerDirection();
	void PlayerDodge();
	void PlayerInput();

	void ShouldMove();
	void Falling();

private:
	UFUNCTION()
	void OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType);

private:
	FRotator PrevRotation;
	class UJHS_WeaponComponent* WeaponComp;


};
