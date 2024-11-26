#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "JHS_Attachment.generated.h"

//Event to be Called by NotifyState
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentBeginCollision);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentEndCollision);

//Overlap Event
//InAttacker = 때린 놈
//InAttackCuaser = 때린놈이 들고 있던 무기
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, class ACharacter*, InAttacker, AActor*, InAttackCuaser, class ACharacter*, InOther);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttachmentEndOverlap, class ACharacter*, InAttacker, class ACharacter*, InOther);

//WeaponType Setting Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttachWeaponType, EWeaponType, InAttachType);

UCLASS()
class TEAM_TTINGJO_API AJHS_Attachment 
	: public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE bool GetHide() { return bIsHide; }

protected://Root Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* Root;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Owner")
	class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Collision")
	TArray<class UShapeComponent*> Collisions;

//Default Function
public:	
	AJHS_Attachment();

protected:
	virtual void BeginPlay() override;
///////////////////////////////////////////////////////////////////////

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnBeginEquip();
	virtual void OnBeginEquip_Implementation() {};

	UFUNCTION(BlueprintNativeEvent)
	void OnEndEquip();
	virtual void OnEndEquip_Implementation() {};

	UFUNCTION(BlueprintNativeEvent)
	void OnUnequip();
	virtual void OnUnequip_Implementation() {};

protected:
	UFUNCTION(BlueprintCallable, Category = "Attach")
	void AttachTo(FName InSocketName);

	UFUNCTION(BlueprintCallable, Category = "Attach")
	void AttachToCollision(FName InCollisionName);

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBOdyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public://Collision On/Off
	void OnCollision();
	void OffCollision();

public://Delegate Value
	//Collision Delegate Value
	FAttachmentBeginCollision OnAttachmentBeginCollision;
	FAttachmentEndCollision OnAttachmentEndCollision;

	//Overlap Delegate Value
	FAttachmentBeginOverlap OnAttachmentBeginOverlap;
	FAttachmentEndOverlap OnAttachmentEndOverlap;

	//AttachWeaponType Delegate Value
	FAttachWeaponType OnAttachWeaponType;

private:
	bool bIsHide;
};
