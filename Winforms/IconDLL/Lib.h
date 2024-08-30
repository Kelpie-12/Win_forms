#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <Windows.h>
#include "resource.h"
#include<string>

#ifdef IconDLL_EXPORTS
#define IconDLL_API _declspec(dllexport)
#else 
#define IconDLL_API _declspec(dllimport)
#endif // 


extern "C" IconDLL_API void SetSkin(HWND & hwnd, LPSTR skin);


extern "C" IconDLL_API void Get_Number_In_IDC_EDIT(HWND& hwnd, int number);
extern "C" IconDLL_API std::string returt_res(std::string res);
extern "C" IconDLL_API void Get_Znar_In_IDC_EDIT(HWND& hwnd, CHAR znak, std::string & rezult);
extern "C" IconDLL_API void Get_SM_Znak(HWND&, int idc);
