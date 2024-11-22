#pragma once

//Output Log, Display Print Log Function Class
//CheckMacro Class

#include "CoreMinimal.h"

//Check Macro
//x가 true 이면 return
#define CheckTrue(x) { if(x == true) return; }
//x가 true 이면 y return
#define CheckTrueResult(x, y) { if(x == true) return y; }

//x가 false 이면 return
#define CheckFalse(x) { if(x == false) return;}
//x가 false 이면 y return
#define CheckFalseResult(x, y) { if(x == false) return y;}

//x가 null 이면 return
#define CheckNull(x) { if(x == nullptr) return;}
//x가 null 이면  y return
#define CheckNullResult(x, y) { if(x == nullptr) return y;}

//Function Line Macro
#define LOG_LINE() { JHS_Global::LOG(__FILE__, __FUNCTION__,__LINE__); }
#define PRINT_LINE() { JHS_Global::PRINT(__FILE__, __FUNCTION__,__LINE__);}

class TEAM_TTINGJO_API JHS_Global
{
public:
	//Custom Log Function
	//LOG(int32)
	static void LOG(int32 InValue);
	//LOG(float)
	static void LOG(float InValue);
	//LOG("내용")
	static void LOG(const FString& InValue);

	//Custom Display Print Log Funtion
	//InValue = int32, InColor = 색, InKey = 순서, InDuration = 표시시간
	static void PRINT(int32 InValue, FColor InColor = FColor::Red, int32 InKey = -1, float InDuration = 5);
	//InValue = float, InColor = 색, InKey = 순서, InDuration = 표시시간
	static void PRINT(float InValue, FColor InColor = FColor::Red, int32 InKey = -1, float InDuration = 5);
	//InValue = TEXT("내용"), InColor = 색, InKey = 순서, InDuration = 표시시간
	static void PRINT(const FString& InValue, FColor InColor = FColor::Red, int32 InKey = -1, float InDuration = 5);
};
