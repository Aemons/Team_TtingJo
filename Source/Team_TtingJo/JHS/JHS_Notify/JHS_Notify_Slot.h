
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "JHS_Notify_Slot.generated.h"

//Temp Notify Class

UENUM()
enum class ESlotType : uint8
{
	FullBody, UpperBody, Max
};

UCLASS()
class TEAM_TTINGJO_API UJHS_Notify_Slot : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	ESlotType Type;

public:
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


};
