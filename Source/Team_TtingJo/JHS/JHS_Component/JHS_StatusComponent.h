#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHS_StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM_TTINGJO_API UJHS_StatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }
	FORCEINLINE bool IsDead() { return CurrentHealth <= 0.0f; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = "HP")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HP")
	float CurrentHealth;

//Default Function
//////////////////////////////////////////////////////////////
public:	
	UJHS_StatusComponent();

protected:
	virtual void BeginPlay() override;
//////////////////////////////////////////////////////////////

public:
	void Damage(float InAmount);

private:
	class ACharacter* OwnerCharacter;

};
