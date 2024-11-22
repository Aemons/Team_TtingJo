#include "JHS_Global.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(GP, Display, All)

void JHS_Global::LOG(int32 InValue)
{
	UE_LOG(GP, Display, L"%d", InValue);
}

void JHS_Global::LOG(float InValue)
{
	UE_LOG(GP, Display, L"%f", InValue);
}

void JHS_Global::LOG(const FString& InValue)
{
	UE_LOG(GP, Display, L"%s", *InValue);
}

void JHS_Global::PRINT(int32 InValue, FColor InColor, int32 InKey, float InDuration)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::FromInt(InValue));
}

void JHS_Global::PRINT(float InValue, FColor InColor, int32 InKey, float InDuration)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
}

void JHS_Global::PRINT(const FString& InValue, FColor InColor, int32 InKey, float InDuration)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue);
}
