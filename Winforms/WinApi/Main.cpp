#include <Windows.h>
#include "resource.h"
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR ipCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "Hello World!\n��������", "��������� ����", MB_YESNOCANCEL| MB_ICONWARNING|MB_DEFBUTTON3);
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL DlgProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG://������������ ������ ���� ���, ��� �������� ����
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		//HWND hEdinLogin = GetDlgItem(hwnd, IDC_EDIT_Login);
		//SetFocus(hEdinLogin);
		//SetFocus(GetDlgItem(hwnd, IDC_EDIT_Login));
	}
	break;
	case WM_COMMAND://�������������� ������� �� ������, ���� ������ � ����� ��������� ��������� ����
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
			MessageBox(hwnd, "���� ������ ��", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE://�������������� ��� ������� �� ������ � (�������)
		EndDialog(hwnd, 0);
	default:
		break;
	}
	return false;
}
