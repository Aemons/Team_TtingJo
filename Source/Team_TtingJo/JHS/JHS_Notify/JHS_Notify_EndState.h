#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"

#include "JHS_Component/JHS_StateComponent.h"

#include "JHS_Notify_EndState.generated.h"

UCLASS()
class TEAM_TTINGJO_API UJHS_Notify_EndState : public UAnimNotify
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Type")
	EStateType StateType;

public:
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
