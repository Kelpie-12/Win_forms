#include <Windows.h>
#include "resource.h"
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR ipCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "Hello World!\nСобщение", "Заголовок окна", MB_YESNOCANCEL| MB_ICONWARNING|MB_DEFBUTTON3);
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL DlgProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam)
{
	CHAR Login[]{ "Введите логин" };
	switch (uMsg)
	{
	case WM_INITDIALOG://отрабатывает только один раз, при создание окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_Login), WM_SETTEXT, 0, (LPARAM)Login);
		//HWND hEdinLogin = GetDlgItem(hwnd, IDC_EDIT_Login);
		//SetFocus(hEdinLogin);
		//SetFocus(GetDlgItem(hwnd, IDC_EDIT_Login));
	}
	break;
	case WM_COMMAND://Обрабатываются нажатия на кнопки, ввод текста и любые изменения состояния окна
		switch (LOWORD(wParan))
		{
		case IDC_BUTTON_Copy:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_Login);
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_Password);
			CONST INT size = 256;
			CHAR sz_buff[size]{};
			SendMessage(hEdit, WM_GETTEXT, size, (LPARAM)sz_buff);
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buff);
		}
		break;
		case IDOK:
			MessageBox(hwnd, "Была нажата ок", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_EDIT_Login:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_Login);
			CONST INT size = 256;
			CHAR sz_buff[size]{};
			SendMessage(hEdit, WM_GETTEXT, size, (LPARAM)sz_buff);
			if (HIWORD(wParan) == EN_SETFOCUS)
			{
				if (!strcmp(sz_buff, Login))
				{
					SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
				}
			}
			else if (HIWORD(wParan) == EN_KILLFOCUS)
			{
				if (strlen(sz_buff) == 0)
				{
					SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)Login);
				}
				else
				{
					SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buff);
				}
			}
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		default:
			break;
		}
		break;
	
	case WM_CLOSE://Обрабатываются при нажатие на кнопку Х (закрыть)
		EndDialog(hwnd, 0);
	default:
		break;
	}
	return false;
}
