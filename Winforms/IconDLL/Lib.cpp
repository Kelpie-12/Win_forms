#define _CRT_SECURE_NO_WARNINGS 
#include "pch.h"
#include "Lib.h"
#include <Windows.h>
#include "resource.h"
#include <string>
#include<vector>

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
		"IDB_BITMAP0",
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


void Get_Number_In_IDC_EDIT(HWND& hwnd, int number)
{
	CHAR sz_buffer[256]{};
	SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_GETTEXT, 256, (LPARAM)sz_buffer);
	std::string buffer = sz_buffer;
	if (buffer.compare("0") == 0 && number != 10)
	{
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 0, (LPARAM)std::to_string(number).c_str());
	}
	else
	{
		if (number == 10)
		{
			if (buffer.find(".") == std::string::npos)
			{
				buffer += ".";
			}
		}
		else
		{
			buffer += std::to_string(number);
		}
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 0, (LPARAM)buffer.c_str());
	}
}

std::string returt_res(std::string res)
{
	std::string operand;
	std::vector<double> num;
	std::string tmp2;

	int ind = res.find_first_of(".");
	//if (ind == std::string::npos)
	//	int (*integer)(const char*) { atoi };
	/*else
		double(*doubler)(const std::string,size_t*(size_t*)) { std::stod() };
	*/
	for (size_t i = 0; i < res.size(); i++)
	{
		if (res[i] != '/' && res[i] != '*' && res[i] != '+' && res[i] != '-')
		{
			tmp2 += res[i];
			if (i == res.size() - 1)
			{
				/*if (ind == std::string::npos)
					num.push_back(atoi(tmp2.c_str()));
				else */
				num.push_back(std::stod(tmp2.c_str()));
				tmp2 = "";
				//operand += res[i];
			}
		}
		else
		{
			/*if (ind == std::string::npos)
				num.push_back(atoi(tmp2.c_str()));
			else*/ num.push_back(std::stod(tmp2.c_str()));
			tmp2 = "";
			operand += res[i];
		}
	}
	int index = 1;
	double r = 0.0;
	while (index != std::string::npos)
	{
		index = operand.find_first_of("*/");
		r = 0;
		if (index != std::string::npos)
		{
			if (operand[index] == '*')
			{
				r = num[index] * num[index + 1];
				num[index] = r;
				num.erase(num.begin() + index + 1);
			}
			if (operand[index] == '/')
			{
				r = num[index] / num[index + 1];
				num[index] = r;
				num.erase(num.begin() + index + 1);
			}
			operand.erase(operand.begin() + index);
		}
	}
	index = 1;
	while (index != std::string::npos)
	{
		index = operand.find_first_of("+-");
		r = 0;
		if (index != std::string::npos)
		{
			if (operand[index] == '+')
			{
				num[index] = num[index] + num[index + 1];
				num.erase(num.begin() + index + 1);
			}
			if (operand[index] == '-')
			{
				num[index] = num[index] - num[index + 1];
				num.erase(num.begin() + index + 1);
			}
			operand.erase(operand.begin() + index);
		}
	}
	tmp2.clear(); ;
	operand += std::to_string(num[0]);
	//if (ind == std::string::npos)
	//{
	//	index = operand.find_first_of(".");
	//	for (size_t i = 0;i < index; i++)
	//	{
	//		tmp2 += operand[i];
	//	}
	//}
	//else tmp2 = operand;
	return operand;
}

void Get_Znar_In_IDC_EDIT(HWND& hwnd, CHAR znak, std::string& rezult)
{
	CHAR sz_buf[256]{};
	SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_GETTEXT, 256, (LPARAM)sz_buf);
	rezult += sz_buf;
	if (rezult[rezult.size() - 1] == '.' || rezult[rezult.size() - 1] == '*' || rezult[rezult.size() - 1] == '+' || rezult[rezult.size() - 1] == '/' || rezult[rezult.size() - 1] == '-') {}
	else
	{
		rezult += znak;
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 256, (LPARAM)rezult.c_str());
	}
	rezult = "";
}

void Get_SM_Znak(HWND& hwnd, int idc)
{
	SendMessage(hwnd, WM_COMMAND, LOWORD(idc), 0);
	SendMessage(GetDlgItem(hwnd, LOWORD(idc)), BM_SETSTATE, TRUE, 0);
	Sleep(75);
	SendMessage(GetDlgItem(hwnd, LOWORD(idc)), BM_SETSTATE, FALSE, 0);
}

//void SetSkin(HWND& hwnd, LPSTR skin)
//{
//	CHAR sz_file[MAX_PATH]{  };
//	for (int i = IDC_BUTTON_0; i <= IDC_BUTTON_9; i++)
//	{
//		HWND hButton = GetDlgItem(hwnd, i);
//		sprintf(sz_file, "ButtonBMP\\%s\\button_%i.bmp", skin, i - IDC_BUTTON_0);
//		HANDLE hImage = LoadImage
//		(
//			NULL,
//			sz_file,
//			IMAGE_BITMAP,
//			i == IDC_BUTTON_0 ? g_i_BUTTON_BOUBLE_SIZE : g_i_BUTTON_SIZE,
//			g_i_BUTTON_SIZE,
//			LR_LOADFROMFILE
//		);
//		SendMessage(hButton, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hImage);
//
//	}
//}

void Get_Error(HWND& hwnd)
{
	DWORD dwErroMessageID = GetLastError();
	LPSTR lpszMessageBUffer = NULL;
	DWORD dwSize = FormatMessage
	(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwErroMessageID,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_RUSSIAN_RUSSIA),
		(LPSTR)&lpszMessageBUffer,
		0,
		NULL
	);
	MessageBox(hwnd, lpszMessageBUffer, "Error", MB_OK | MB_ICONERROR);
}

