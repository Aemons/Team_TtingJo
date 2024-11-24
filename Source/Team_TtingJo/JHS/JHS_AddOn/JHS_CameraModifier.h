#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "JHS_CameraModifier.generated.h"

UCLASS()
class TEAM_TTINGJO_API UJHS_CameraModifier : public UCameraModifier
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetLocation(const FVector& InLocation) { Location = InLocation; }
	FORCEINLINE void SetRotation(const FRotator& InRotation) { Rotation = InRotation; }
protected:
	//���� View���� �޾ƿͼ� �Լ����ο��� ����� New���� �������ִ� �Լ�
	void ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV) override;

private:
	FVector Location;
	FRotator Rotation;
	
};
