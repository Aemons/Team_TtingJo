#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

//FDamageEvent Header
#include "Engine/DamageEvents.h"

#include "JHS_WeaponStructures.generated.h"

USTRUCT()
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bUseControllerRotation = true;
};

USTRUCT()
struct FMainActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

public:
	void MainAction(class ACharacter* InOwner);
};

USTRUCT()
struct  FHitData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float Launch = 100.0f;

	UPROPERTY(EditAnywhere)
	float HitStopTime;

	UPROPERTY(EditAnywhere)
	class USoundWave* Sound;

	UPROPERTY(EditAnywhere)
	class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
	FVector EffectLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FVector EffectScale = FVector::OneVector;

public:
	void SendDamage(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther);
	void PlayMontage(class ACharacter* InOwner);
	void PlayHitStop(UWorld* InWorld);
	void PlaySoundWave(class ACharacter* InOwner);
	void PlayEffect(UWorld* InWorld, const FVector& InLocation, const FRotator& InRotation);
};


USTRUCT()
struct FMainActionDamageEvent
	: public FDamageEvent
{
	GENERATED_BODY()

public:
	FHitData* HitData;
};

UCLASS()
class TEAM_TTINGJO_API UJHS_WeaponStructures : public UObject
{
	GENERATED_BODY()
	
};
