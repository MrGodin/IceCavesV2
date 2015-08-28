#pragma once
#include "wchar.h"
#include "windows.h"

static WCHAR strBuffer[512] = { '\0' };
class wString
{
	

	static WCHAR* WCharTranslate(WCHAR* strMsg, ...)
	{

		va_list args;
		va_start(args, strMsg);
		vswprintf_s(strBuffer, 512, strMsg, args);
		strBuffer[511] = L'\0';
		va_end(args);

		return (strBuffer);
	}

public:
	static void toChar(WCHAR* wc_str,char* c_str)
	{
		wsprintf(strBuffer, L"%s", wc_str);
		char cBuffer[512];
		int ret;
		size_t len = wcslen(strBuffer) + 1;
		ret = wcstombs_s(&len, cBuffer, strBuffer, sizeof(cBuffer));
		if (ret == 512) cBuffer[511] = '\0';
		sprintf_s(c_str, len, "%s", cBuffer);
		
	}
	static void toFloatPercision2(const float& val,WCHAR* str)
	{
		wsprintf(str, L"%s", WCharTranslate(L"%0.2f", val));
		
	}
	static void toFloatPercision4(const float& val, WCHAR* str)
	{
		wsprintf(str, L"%s", WCharTranslate(L"%0.4f", val));

	}
	
	static void toInt(const int& val, WCHAR* str)
	{
		wsprintf(str, L"%s", WCharTranslate(L"%d", val));

	}
	static void toUint(const UINT& val, WCHAR* str)
	{
		wsprintf(str, L"%s", WCharTranslate(L"%u", val));

	}
	static void toLong(const long& val, WCHAR* str)
	{
		wsprintf(str, L"%s", WCharTranslate(L"%u", val));

	}
};