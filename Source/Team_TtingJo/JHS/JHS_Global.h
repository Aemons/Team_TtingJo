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
#define LOG_LINE() { JHS_Global::LOG(__FILE__, __FUNCTION__, __LINE__); }
#define PRINT_LINE() { JHS_Global::PRINT_LINE_FUNC(FString(__FILE__), FString(__FUNCTION__), __LINE__); }

//PRINT �Լ����� �������� ���� InValue�� �����ؼ� ���
#define VALUE_STRING(x, y) {FString::Printf(TEXT(x), y)}

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
	//InValue = int32, InColor = ��, InKey = ����, InDuration = ǥ�ýð�
	static void PRINT(int32 InValue, int32 InKey = -1, FColor InColor = FColor::Red, float InDuration = 5);
	//InValue = float, InColor = ��, InKey = ����, InDuration = ǥ�ýð�
	static void PRINT(float InValue, int32 InKey = -1, FColor InColor = FColor::Red, float InDuration = 5);

	//InValue = "����", InColor = ��, InKey = ����, InDuration = ǥ�ýð�
	static void PRINT(const FString& InValue, int32 InKey = -1, FColor InColor = FColor::Red, float InDuration = 5);

	//Macro Call Function
	static void PRINT_LINE_FUNC(const FString& InFile, const FString& InFunc, int32 InLine, FColor InColor = FColor::Yellow, int32 InKey = 0, float InDuration = 5);
};
