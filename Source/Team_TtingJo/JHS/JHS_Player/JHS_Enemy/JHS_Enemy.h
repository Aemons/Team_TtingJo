#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JHS_Enemy.generated.h"

UCLASS()
class TEAM_TTINGJO_API AJHS_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	AJHS_Enemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
