#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "JHS_WeaponStructures.h"

#include "JHS_WeaponDataAsset.generated.h"

UCLASS()
class TEAM_TTINGJO_API UJHS_WeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE class AJHS_Attachment* GetAttachment() { return Attachment; }
	FORCEINLINE class UJHS_Equipment* GetEquipment() { return Equipment; }
	FORCEINLINE class UJHS_MainAction* GetMainAction() { return MainAction; }

private://Weapon Class
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AJHS_Attachment> AttachmentClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJHS_Equipment> EquipmentClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJHS_MainAction> MainActionClass;

private://Weapon Class Default Data Setting
	UPROPERTY(EditAnywhere)
	FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere)
	TArray<FMainActionData> MainActionData;

	UPROPERTY(EditAnywhere)
	TArray<FHitData> HitDatas;

private://Weapon Class Object
	UPROPERTY()
	class AJHS_Attachment* Attachment;

	UPROPERTY()
	class UJHS_Equipment* Equipment;

	UPROPERTY()
	class UJHS_MainAction* MainAction;

public:
	UJHS_WeaponDataAsset();

	void BeginPlay(class ACharacter* InOwner);
};
