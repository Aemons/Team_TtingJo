#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHS_MovemetComponent.generated.h"

UENUM()
enum class ESpeedType : uint8
{
	Walk, Jog, Run, Max
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM_TTINGJO_API UJHS_MovemetComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed[(int32)ESpeedType::Max] = { 200, 400, 600 };

public:
	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ESpeedType::Walk]; }
	FORCEINLINE float GetJogSpeed() { return Speed[(int32)ESpeedType::Jog]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ESpeedType::Run]; }
//Default Function
public:	
	UJHS_MovemetComponent();

protected:
	virtual void BeginPlay() override;
////////////////////////////////////////////////////////////////////////

public:
	void SetSpeed(ESpeedType InType);

	void OnWalk();
	void OnJog();
	void OnRun();

	void Move();
	void Stop();

	void EnableControlRotation();
	void DisableControlRotation();

private:
	class ACharacter* OwnerCharacter;
	bool bCanMove = true;

};
