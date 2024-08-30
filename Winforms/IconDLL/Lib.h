#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <Windows.h>
#include "resource.h"

#ifdef IconDLL_EXPORTS
#define IconDLL_API _declspec(dllexport)
#else 
#define IconDLL_API _declspec(dllimport)
#endif // 


extern "C" IconDLL_API void SetSkin(HWND & hwnd, LPSTR skin);

