#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHS_WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM_TTINGJO_API UJHS_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UJHS_WeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
