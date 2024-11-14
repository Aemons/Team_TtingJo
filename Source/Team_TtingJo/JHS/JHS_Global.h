#pragma once

//Output Log, Display Print Log Function Class
//CheckMacro Class

#include "CoreMinimal.h"

//Check Macro
//x�� true �̸� return
#define CheckTrue(x) { if(x == true) return; }
//x�� true �̸� y return
#define CheckTrueResult(x, y) { if(x == true) return y; }

//x�� false �̸� return
#define CheckFalse(x) { if(x == false) return;}
//x�� false �̸� y return
#define CheckFalseResult(x, y) { if(x == false) return y;}

//x�� null �̸� return
#define CheckNull(x) { if(x == nullptr) return;}
//x�� null �̸�  y return
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
	//LOG("����")
	static void LOG(const FString& InValue);

	//Custom Display Print Log Funtion
	//InValue = int32, InKey = ����, InDuration = ǥ�ýð�, InColor = ��
	static void PRINT(int32 InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue);
	//InValue = float, InKey = ����, InDuration = ǥ�ýð�, InColor = ��
	static void PRINT(float InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue);
	//InValue = TEXT("����"), InKey = ����, InDuration = ǥ�ýð�, InColor = ��
	static void PRINT(const FString& InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue);
};
