#include <Windows.h>
#include<string>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam);
CONST CHAR* values[] = { "This","is","my","first","Combo","box" };
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR ipCmdLine, INT nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)values[i]);
		}
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParan))
		{
		case IDOK:
			INT index = SendMessage(GetDlgItem(hwnd, IDC_COMBO1), CB_GETCURSEL, 0, 0);
			std::string text{ "Не выбран ни один пункт меню" };
			if (index >= 0)
			{
				text = "";
				text = { "Выбран пункт меню -> " };
				text += std::to_string(index);
				text += " -> ";
				text += values[index];
			}
			MessageBox(hwnd, text.c_str(), "Info", MB_OKCANCEL);
			break;
			//default:
				//break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	default:
		break;
	}
	return false;
}
