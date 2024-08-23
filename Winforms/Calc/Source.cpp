#include <Windows.h>
#include "resource.h"
#include <string>

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

void Get_Number_In_IDC_EDIT(HWND& hwnd, int number);

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
	wc.lpfnWndProc = (WNDPROC)WndProc;//Указатель на процедуру окна
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


INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam)
{

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
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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

		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_BUTTON_X, g_i_START_BUTTON_Y + (g_i_INTERVAL + g_i_BUTTON_SIZE) * 3,
			g_i_BUTTON_BOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			NULL, NULL
		);
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
				(HMENU)IDC_BUTTON_PLUS + i,
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
			if (buf.size() > 1)
			{
				buf.erase(buf.begin() + buf.size() - 1);
			}
			//if (buf.size() == 1)
			//	buf = std::to_string(0);

			SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 0, (LPARAM)buf.c_str());
		}
		break;

		default:
			break;
		}
		break;
	case WM_KEYDOWN:
	{
		if (LOWORD(wParan) >= 0x30 && LOWORD(wParan) <= 0x39)
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParan - 0x30 + IDC_BUTTON_0), 0);

		switch (LOWORD(wParan))
		{
		case VK_OEM_PERIOD:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0);
			break;
		case VK_OEM_PLUS:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0);
			break;
		case VK_OEM_MINUS:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0);
			break;
		case VK_MULTIPLY:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0);
			break;
		case VK_DIVIDE:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_SLASH), 0);
			break;
		case VK_BACK:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0);
			break;
		default:
			break;
		}

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