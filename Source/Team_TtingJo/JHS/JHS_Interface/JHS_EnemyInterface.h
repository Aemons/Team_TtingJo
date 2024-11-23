#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JHS_EnemyInterface.generated.h"

UINTERFACE(MinimalAPI)
class UJHS_EnemyInterface : public UInterface
{
	GENERATED_BODY()
};

class TEAM_TTINGJO_API IJHS_EnemyInterface
{
	GENERATED_BODY()

public://State 변경 전달 Interface 함수
	virtual void End_Hitted() {}
	virtual void End_Dead() {}

};
