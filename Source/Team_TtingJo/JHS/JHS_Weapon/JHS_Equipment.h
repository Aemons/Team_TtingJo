#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "JHS_WeaponStructures.h"

#include "JHS_Equipment.generated.h"

//Weapon Equip Class

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentBeginEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentEndEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentUnequip);

UCLASS()
class TEAM_TTINGJO_API UJHS_Equipment : public UObject
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool GetBeginEquip() { return bBeginEquip; }
	FORCEINLINE const bool* GetEquipped() { return &bEquipped; }

protected:
	UPROPERTY(BlueprintReadOnly)
	class ACharacter* OwnerCharacter;

public:
	void BeginPlay(ACharacter* InOwner, const FEquipmentData& InData);

public:
	void Equip();
	void Unequip();

	void Begin_Equip();
	void End_Equip();

public://Delegate Value
	FEquipmentEquip OnEquipmentEquip;
	FEquipmentBeginEquip OnEquipmentBeginEquip;
	FEquipmentEndEquip OnEquipmentEndEquip;
	FEquipmentUnequip OnEquipmentUnequip;

private:
	FEquipmentData Data;

	bool bBeginEquip;
	bool bEquipped = false;

	class UJHS_StateComponent* StateComp;
	class UJHS_MovemetComponent* MovementComp;
};
