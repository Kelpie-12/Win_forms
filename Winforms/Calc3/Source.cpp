#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "resource.h"
#include <string>
#include <vector> 
#include "Lib.h"

//https://github.com/microsoft/Windows-classic-samples
CONST CHAR g_sz_WINDOW_CLASS[] = "Calc_PD_311";
CONST INT g_i_START_Y = 10;
CONST INT g_i_START_X = 10;

CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_INTERVAL = 5;
CONST INT g_i_BUTTON_BOUBLE_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;


CONST INT g_i_DISPLAY_WIDTH = (g_i_BUTTON_SIZE + g_i_INTERVAL) * 5;
CONST INT g_i_DISPLAY_HEIGHT = 22;

CONST INT g_i_WNNDOW_HEIGHT_TOOL = 39;
CONST INT g_i_WINDOW_WIDTH = g_i_DISPLAY_WIDTH + g_i_START_X * 2 + 16;
CONST INT g_i_WINDOW_HEIGHT = g_i_DISPLAY_HEIGHT + g_i_WNNDOW_HEIGHT_TOOL + g_i_START_Y * 2 + 5 + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4;

CONST INT g_i_START_BUTTON_Y = g_i_START_Y * 2 + g_i_DISPLAY_HEIGHT;
CONST INT g_i_START_BUTTON_X = g_i_START_X;

CONST INT g_i_START_X_OPERATIONS = g_i_START_BUTTON_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3;
CONST INT g_i_START_X_CONTROL_BUTTONS = g_i_START_BUTTON_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4;

//void SetSkin(HWND& hwnd, LPSTR skin);
//void Get_Error(HWND& hwnd);

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR ipCmdLine, INT nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	wc.hIcon = HICON(LoadImage(hInstance, "Icon\\icon2.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE));
	wc.hIconSm = HICON(LoadImage(hInstance, "Icon\\icon2.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = HBRUSH(COLOR_WINDOW);

	wc.lpszClassName = g_sz_WINDOW_CLASS;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC)WndProc;//��������� �� ��������� ����
	wc.hInstance = hInstance;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registation failed", "Error", MB_OK | MB_ICONERROR);
	}

	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
std::string rezult;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam)
{
	static CONST CHAR DEFALULT_SKIN[] = "square_blue";
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hDisplay = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_RIGHT | ES_READONLY | WS_BORDER,
			g_i_START_X, g_i_START_Y,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd, (HMENU)IDC_EDIT_DISPLAY, NULL, NULL
		);

		//---------------DIGTH---------------//
		INT digit = 0;
		CHAR sz_digit[2]{};
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = '1' + digit;
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
					g_i_START_BUTTON_X + j * (g_i_BUTTON_SIZE + g_i_INTERVAL),
					g_i_START_BUTTON_Y + i * (g_i_BUTTON_SIZE + g_i_INTERVAL),
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_1 + digit++),
					NULL,
					NULL
				);
			}
		}

		HWND hButtonDigit_0 = CreateWindowEx
		(
			NULL, "Button", "0",//
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_START_BUTTON_X, g_i_START_BUTTON_Y + (g_i_INTERVAL + g_i_BUTTON_SIZE) * 3,
			g_i_BUTTON_BOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			NULL, NULL
		);
		SetSkin(hwnd, (LPSTR)DEFALULT_SKIN);
		//Get_Error(hwnd);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_BUTTON_X + g_i_BUTTON_BOUBLE_SIZE + g_i_INTERVAL, g_i_START_BUTTON_Y + (g_i_INTERVAL + g_i_BUTTON_SIZE) * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			NULL, NULL
		);
		CONST CHAR sz_operations[] = "+-*/";
		CHAR sz_operation[2] = "";
		for (size_t i = 0; i < 4; i++)
		{
			sz_operation[0] = sz_operations[i];
			CreateWindowEx
			(
				NULL, "Button", sz_operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				g_i_START_X_OPERATIONS, g_i_START_BUTTON_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS + i),
				NULL, NULL
			);
		}

		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X_CONTROL_BUTTONS, g_i_START_BUTTON_Y,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			NULL, NULL
		);

		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X_CONTROL_BUTTONS, g_i_START_BUTTON_Y + g_i_BUTTON_SIZE + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLEAR,
			NULL, NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X_CONTROL_BUTTONS, g_i_START_BUTTON_Y + g_i_BUTTON_BOUBLE_SIZE + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_BOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			NULL, NULL
		);

	}
	break;
	case WM_COMMAND:
		SetFocus(hwnd);
		switch (LOWORD(wParan))
		{
		case IDC_BUTTON_0:
		case IDC_BUTTON_1:
		case IDC_BUTTON_2:
		case IDC_BUTTON_3:
		case IDC_BUTTON_4:
		case IDC_BUTTON_5:
		case IDC_BUTTON_6:
		case IDC_BUTTON_7:
		case IDC_BUTTON_8:
		case IDC_BUTTON_9:
		case IDC_BUTTON_POINT:
			Get_Number_In_IDC_EDIT(hwnd, (INT)(wParan % 100));
			break;
		case IDC_BUTTON_CLEAR:
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 0, (LPARAM)"0");
			break;
		case IDC_BUTTON_BSP:
		{
			CHAR tmp[256]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_GETTEXT, 256, (LPARAM)tmp);
			std::string buf = tmp;
			if (buf.size() == 1)
				buf = std::to_string(0);
			if (buf.size() > 1)
				buf.erase(buf.begin() + buf.size() - 1);
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 0, (LPARAM)buf.c_str());
		}
		break;
		case IDC_BUTTON_PLUS:
			Get_Znar_In_IDC_EDIT(hwnd, '+',rezult);

			break;
		case IDC_BUTTON_MINUS:
			Get_Znar_In_IDC_EDIT(hwnd, '-',rezult);

			break;
		case IDC_BUTTON_ASTER:
			Get_Znar_In_IDC_EDIT(hwnd, '*', rezult);
			break;
		case IDC_BUTTON_SLASH:
			Get_Znar_In_IDC_EDIT(hwnd, '/', rezult);
			break;
		case IDC_BUTTON_EQUAL:
		{
			CHAR sz_buf[256]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_GETTEXT, 256, (LPARAM)sz_buf);
			std::string otvet = returt_res(sz_buf);
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 256, (LPARAM)otvet.c_str());
		}
		break;
		default:
			break;
		}
		break;
	case WM_KEYDOWN:
	{
		if (LOWORD(wParan) >= 0x30 && LOWORD(wParan) <= 0x39)
		{
			//SendMessage(hwnd, WM_COMMAND, LOWORD(wParan - 0x30 + IDC_BUTTON_0), 0);
			SendMessage(GetDlgItem(hwnd, LOWORD(wParan - 0x30 + IDC_BUTTON_0)), BM_SETSTATE, TRUE, 0);
			Sleep(75);
			SendMessage(GetDlgItem(hwnd, LOWORD(wParan - 0x30 + IDC_BUTTON_0)), BM_SETSTATE, FALSE, 0);
		}
		if (LOWORD(wParan) >= 0x60 && LOWORD(wParan) <= 0x69)
		{
			//SendMessage(hwnd, WM_COMMAND, LOWORD(wParan - 0x60 + IDC_BUTTON_0), 0);
			SendMessage(GetDlgItem(hwnd, LOWORD(wParan - 0x60 + IDC_BUTTON_0)), BM_SETSTATE, TRUE, 0);
			Sleep(75);
			SendMessage(GetDlgItem(hwnd, LOWORD(wParan - 0x60 + IDC_BUTTON_0)), BM_SETSTATE, FALSE, 0);
		}
		switch (LOWORD(wParan))
		{
		case VK_OEM_PERIOD:
			Get_SM_Znak(hwnd, IDC_BUTTON_POINT);
			break;
		case VK_OEM_PLUS:
			Get_SM_Znak(hwnd, IDC_BUTTON_PLUS);
			break;
		case VK_OEM_MINUS:
			Get_SM_Znak(hwnd, IDC_BUTTON_MINUS);
			break;
		case VK_MULTIPLY:
			Get_SM_Znak(hwnd, IDC_BUTTON_ASTER);
			break;
		case VK_DIVIDE:
			Get_SM_Znak(hwnd, IDC_BUTTON_SLASH);
			break;
		case VK_BACK:
			Get_SM_Znak(hwnd, IDC_BUTTON_BSP);
			break;
		case VK_ESCAPE:
			Get_SM_Znak(hwnd, IDC_BUTTON_CLEAR);
			break;
		default:
			break;
		}
	}
	break;
	case WM_KEYUP:
	{
		if (LOWORD(wParan) >= 0x30 && LOWORD(wParan) <= 0x39)
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParan - 0x30 + IDC_BUTTON_0), 0);
		if (LOWORD(wParan) >= 0x60 && LOWORD(wParan) <= 0x69)
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParan - 0x60 + IDC_BUTTON_0), 0);
	}
	break;
	case WM_CTLCOLOREDIT:
	{
		//HDC hdc = (HDC)wParan;
		//SetBkMode(hdc, OPAQUE);
		//SetBkColor(hdc, RGB(0, 0, 155));
		//HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 200));
		//SetTextColor(hdc, RGB(0, 0, 255));
		//SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
		//SendMessage(hwnd, WM_ERASEBKGND, wParan, 0);
		////SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 0, (LPARAM)"0");
		//ReleaseDC(hwnd, hdc);

		//HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		//HDC hdcEditDisplay = GetDC(hEditDisplay);
		//HBRUSH hBrushDisplay = CreateSolidBrush(RGB(200, 0, 0));
		//SetTextColor(hdcEditDisplay, RGB(0, 0, 255));
		//SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushDisplay);
		//
		//SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 0, (LPARAM)"0");
		//ReleaseDC(hwnd, hdcEditDisplay);

		//return (LRESULT)hBrush;
	}
	break;
	case WM_CONTEXTMENU:
	{
		HMENU hMainMenu = CreatePopupMenu();
		HMENU hSubMenu = CreatePopupMenu();

		InsertMenu(hMainMenu, 0, MF_BYPOSITION | MF_STRING, CM_EXIT, "Exit");
		InsertMenu(hMainMenu, 0, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
		InsertMenu(hMainMenu, 0, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hSubMenu, "Skins");
		InsertMenu(hSubMenu, 0, MF_BYPOSITION | MF_STRING, CM_SQUARE_GREEN, "Square green");
		InsertMenu(hSubMenu, 0, MF_BYPOSITION | MF_STRING, CM_SQUARE_BLUE, "Square blue");

		BOOL item = TrackPopupMenuEx(hMainMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN | TPM_RETURNCMD, LOWORD(lParam), HIWORD(lParam), hwnd, NULL);
		switch (item)
		{
		case CM_SQUARE_BLUE: SetSkin(hwnd, (LPSTR)"square_blue"); break;
		case CM_SQUARE_GREEN: SetSkin(hwnd, (LPSTR)"square_green"); break;
		case CM_EXIT:DestroyWindow(hwnd);	break;

		default:
			break;
		}
		HDC hdc = GetDC(hwnd);
		SendMessage(hwnd, WM_CTLCOLOREDIT, (WPARAM)hdc, 0);


		ReleaseDC(hwnd, hdc);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParan, lParam);
		break;
	}
	return 0;
}



