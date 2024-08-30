#define _CRT_SECURE_NO_WARNINGS 
#include "pch.h"
#include "Lib.h"
#include <Windows.h>
#include "resource.h"
#include <string>

CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_INTERVAL = 5;
CONST INT g_i_BUTTON_BOUBLE_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;
void SetSkin(HWND& hwnd, LPSTR skin)
{
    HMODULE hDLL = LoadLibrary("C:\\Users\\roman\\source\\repos\\Win_forms\\Winforms\\x64\\Debug\\IconDLL.dll");
    if (hDLL == NULL)
    {
        return;
    }
    CHAR sz_file1[MAX_PATH]{  };
    sprintf_s(sz_file1, "%s\\button_%i.bmp", skin, IDB_BITMAP0);
   // HANDLE hImage =LoadImage(hDLL, MAKEINTRESOURCE(1000), IMAGE_BITMAP, g_i_BUTTON_BOUBLE_SIZE, g_i_BUTTON_SIZE, LR_CREATEDIBSECTION)/*LoadBitmap(hDLL, MAKEINTRESOURCEA(0))*/;
    HANDLE hImage = LoadImageA
    (
        hDLL,
        "button_1.bmp",
        IMAGE_BITMAP,
        g_i_BUTTON_SIZE,
        g_i_BUTTON_SIZE,
        LR_LOADFROMFILE
    );
   // auto hIcon= LoadIcon(NULL, MAKEINTRESOURCE(IDB_BITMAP0));

    //HICON hIcon2 = (HICON)LoadImage(hDLL, MAKEINTRESOURCE(IDB_BITMAP0), IMAGE_BITMAP, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE, 0);
    //ICONINFO iconinfo;
    //GetIconInfo(hIcon, &iconinfo);
    //HBITMAP hBitmap = iconinfo.hbmColor;
  // BITMAP(hIcon2);
   // auto hImage2 = LoadBitmap(hDLL, MAKEINTRESOURCE(IDB_BITMAP0) );
   // SendMessage(GetDlgItem(hwnd, 1000), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(hImage2));
   // auto hIcon = LoadIcon(hDLL, MAKEINTRESOURCE(IDB_BITMAP0));
    //HANDLE hImage = LoadImageA(hDLL, "button_1.bmp");
    auto a = GetLastError(); 
	/*CHAR sz_file[MAX_PATH]{  };
	for (int i = IDB_BITMAP0; i <= IDB_BITMAP9; i++)
	{
		HWND hButton = GetDlgItem(hwnd, i);
		sprintf_s(sz_file, "ButtonBMP\\%s\\button_%i.bmp", skin, i - IDB_BITMAP0);
		HANDLE hImage = LoadImage
		(
			NULL,
			(LPCSTR)sz_file,
			IMAGE_BITMAP,
			i == IDB_BITMAP0 ? g_i_BUTTON_BOUBLE_SIZE : g_i_BUTTON_SIZE,
			g_i_BUTTON_SIZE,
			LR_LOADFROMFILE
		);
		
		SendMessage(hButton, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hImage);

	}*/
}