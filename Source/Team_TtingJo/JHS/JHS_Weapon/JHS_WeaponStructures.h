#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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


UCLASS()
class TEAM_TTINGJO_API UJHS_WeaponStructures : public UObject
{
	GENERATED_BODY()
	
};
