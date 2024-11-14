#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JHS_Attachment.generated.h"

UCLASS()
class TEAM_TTINGJO_API AJHS_Attachment : public AActor
{
	GENERATED_BODY()
	
public:	
	AJHS_Attachment();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
