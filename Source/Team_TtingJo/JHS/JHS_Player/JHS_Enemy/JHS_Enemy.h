#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "JHS_Component/JHS_StateComponent.h"
#include "JHS_Interface/JHS_EnemyInterface.h"

#include "JHS_Enemy.generated.h"

UCLASS()
class TEAM_TTINGJO_API AJHS_Enemy 
	: public ACharacter
	, public IJHS_EnemyInterface
{
	GENERATED_BODY()

public://Blueprint Check
	UPROPERTY(EditAnywhere, Category = "Damage")
	float HittedDamage;

	UPROPERTY(EditAnywhere, Category = "Damage")
	bool bIsHit;

	UPROPERTY(EditAnywhere, Category = "Dead Montage")
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere, Category = "Dead Montage")
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Dead Montage")
	FVector2D DeadPoseChance = FVector2D(0.0, 1.0);

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UJHS_WeaponComponent* WeaponComp;

	UPROPERTY(VisibleDefaultsOnly)
	class UJHS_MovemetComponent* MovementComp;

	UPROPERTY(VisibleDefaultsOnly)
	class UJHS_StateComponent* StateComp;

	UPROPERTY(VisibleDefaultsOnly)
	class UJHS_StatusComponent* StatusComp;
//Default Function
/////////////////////////////////////////////////////////////////
public:
	AJHS_Enemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

/////////////////////////////////////////////////////////////////

private://Enemy의 상태를 바꿔주는 함수
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

public://실질적으로 Enemy가 Damage를 받는 함수
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private://EnemyState 변경 함수
	virtual void Hitted();
	virtual void Dead();

	//Enemy가 맞으면 일정거리 만큼 밀어주는 함수 
	void LaunchToEnemy();

	//죽기전의 모습을 저장하는 함수
	void CreateDeathPose();

public:
	void End_Hitted() override;
	void End_Dead() override;

private:
	struct FDamageData
	{
		float Power;
		class ACharacter* Character;
		class AActor* Causer;

		struct FMainActionDamageEvent* Event;
	}Damage;

	bool bIsChance = false;

};
