#include <Windows.h>
#include<string>
#include<vector>
#include<algorithm>
#include "resource.h"
void SortListBox(HWND &hwnd)
{
	HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
	std::vector<std::string> buff;
	CONST INT size = 256;
	CHAR tmp[size]{};
	auto count = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
	for (size_t i = 0; i < count; i++)
	{
		SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)tmp);
		buff.push_back(tmp);
	}
	for (size_t i = 0; i < buff.size(); i++)
	{
		SendMessage(hListBox, LB_DELETESTRING, 0, 0);
	}
	std::sort(buff.begin(), buff.end());

	for (size_t i = 0; i < buff.size(); i++)
	{
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)buff[i].c_str());
	}
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam);
CONST CHAR* values[] = { "Amstedam", "Berlin", "Moscow", "Paris", "Bern", "Helsinki" };
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR ipCmdLine, INT nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam)
{
	CHAR Add[]{ "Add another city" };
	CHAR Delete[]{ "Delete city" };

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)values[i]);
		}
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_ADD), WM_SETTEXT, 0, (LPARAM)Add);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_DELETE), WM_SETTEXT, 0, (LPARAM)Delete);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParan))
		{
		case IDC_BUTTON_ADD:
		{
			HWND hAdd = GetDlgItem(hwnd, IDC_BUTTON_ADD);
			HWND hEditAdd = GetDlgItem(hwnd, IDC_EDIT_ADD);
			CONST INT size = 256;
			CHAR sz_buff[size]{};
			SendMessage(hEditAdd, WM_GETTEXT, size, (LPARAM)sz_buff);
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);

			if (!strcmp(sz_buff, Add))
			{

			}
			else
			{
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buff);
			}
			auto check = SendMessage(GetDlgItem(hwnd, IDC_CHECK_SORT), BM_GETCHECK, 0, 0);
			if (check)
			{
				SortListBox(hwnd);
			}
		}
		break;
		case IDC_BUTTON_DELETE:
		{
			HWND hDelete = GetDlgItem(hwnd, IDC_BUTTON_DELETE);
			HWND hEditDelete = GetDlgItem(hwnd, IDC_EDIT_DELETE);
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			CONST INT size = 256;
			CHAR sz_buff[size]{};
			SendMessage(hEditDelete, WM_GETTEXT, size, (LPARAM)sz_buff);	
			std::string buf = sz_buff;		
			std::vector<std::string> buff;
			CHAR tmp[size]{};
			for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++)
			{
				SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)tmp);
				buff.push_back(tmp);				
			}
			for (size_t i = 0; i < buff.size(); i++)
			{
				if (buf==buff[i])
				{
					SendMessage(hListBox, LB_DELETESTRING, i, 0);
					break;
				}
			}
		}
		break;
		case IDC_EDIT_ADD:
		{
			HWND hEditAdd = GetDlgItem(hwnd, IDC_EDIT_ADD);
			CONST INT size = 256;
			CHAR sz_buff[size]{};
			SendMessage(hEditAdd, WM_GETTEXT, size, (LPARAM)sz_buff);
			if (HIWORD(wParan) == EN_SETFOCUS)
			{
				if (!strcmp(sz_buff, Add))
				{
					SendMessage(hEditAdd, WM_SETTEXT, 0, (LPARAM)"");
				}
			}
			else if (HIWORD(wParan) == EN_KILLFOCUS)
			{
				if (strlen(sz_buff) == 0)
				{
					SendMessage(hEditAdd, WM_SETTEXT, 0, (LPARAM)Add);
				}
				else
				{
					SendMessage(hEditAdd, WM_SETTEXT, 0, (LPARAM)sz_buff);
				}
			}
		}
		break;
		case IDC_EDIT_DELETE:
		{
			HWND hEditAdd = GetDlgItem(hwnd, IDC_EDIT_DELETE);
			CONST INT size = 256;
			CHAR sz_buff[size]{};
			SendMessage(hEditAdd, WM_GETTEXT, size, (LPARAM)sz_buff);
			if (HIWORD(wParan) == EN_SETFOCUS)
			{
				if (!strcmp(sz_buff, Delete))
				{
					SendMessage(hEditAdd, WM_SETTEXT, 0, (LPARAM)"");
				}
			}
			else if (HIWORD(wParan) == EN_KILLFOCUS)
			{
				if (strlen(sz_buff) == 0)
				{
					SendMessage(hEditAdd, WM_SETTEXT, 0, (LPARAM)Delete);
				}
				else
				{
					SendMessage(hEditAdd, WM_SETTEXT, 0, (LPARAM)sz_buff);
				}
			}
		}
		break;

		case IDC_CHECK_SORT:
		{
			HWND hCheckSort = GetDlgItem(hwnd, IDC_CHECK_SORT);
			auto check = SendMessage(hCheckSort, BM_GETCHECK, 0, 0);
			if (check == 1)
			{				
				SortListBox(hwnd);
			}			
		}
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