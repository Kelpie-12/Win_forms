#include <Windows.h>
//#define Text_Element
#include <string>
#include <vector>
#include <stdlib.h>
#ifdef Text_Element
#define IDC_STATIC_TEXT 1000
#define IDC_EDIT 1001
#define IDC_BUTTON 1002  
#endif // Text_Element

#define IDC_COMBO 1001
#define IDC_STATIC 1000
#define IDC_BUTTON 1002  

void size_screen_now(HWND& hwnd);
void set_cursor(HWND& hwnd, HCURSOR& hCursor);
std::string dir_way(HWND& hwnd);



CONST CHAR g_sz_WINDW_CLASS[] = "MY first Window";
//BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam);
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR ipCmdLine, INT nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	//wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIcon = HICON(LoadImage(hInstance, "image_1.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE));
	wc.hIconSm = HICON(LoadImage(hInstance, "Image_2.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//NULL;
	wc.hbrBackground = HBRUSH(COLOR_WINDOW);

	wc.lpszClassName = g_sz_WINDW_CLASS;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.hInstance = hInstance;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	double percentage_reduction = 0.25;
	int screen_x_size = GetSystemMetrics(SM_CXSCREEN);
	int screen_y_size = GetSystemMetrics(SM_CYSCREEN);
	int ax = screen_x_size - (screen_x_size * percentage_reduction);
	int ay = screen_y_size - (screen_y_size * percentage_reduction);
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDW_CLASS,
		g_sz_WINDW_CLASS,
		WS_OVERLAPPEDWINDOW,
		screen_x_size * (percentage_reduction / 2),
		screen_y_size * (percentage_reduction / 2),
		ax,
		ay,
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

}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParan, LPARAM lParam)
{

	BOOL change_cursor = false;
	switch (uMsg)
	{
	case WM_CREATE:
	{
#ifdef Text_Element
		HWND hStatic = CreateWindowEx
		(
			SS_BLACKFRAME, "Static", "This is static text",
			WS_CHILDWINDOW | WS_BORDER | WS_VISIBLE,
			100, 100,
			200, 20,
			hwnd, (HMENU)IDC_STATIC_TEXT,
			NULL, NULL
		);
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "Введите текст",
			WS_CHILD | WS_VISIBLE,
			120, 20,
			200, 20,
			hwnd,
			(HMENU)IDC_EDIT,
			NULL, NULL
		);
		HWND hButton = CreateWindowEx
		(
			NULL, "Button", "Применить",
			WS_CHILD | WS_VISIBLE,
			150, 55,
			75, 35,
			hwnd,
			(HMENU)IDC_BUTTON,
			NULL, NULL
		);
#endif // Text_Element
		size_screen_now(hwnd);

		HWND hStatic = CreateWindowEx
		(
			NULL, "Static", "Выберите указатель мыши: ",
			WS_CHILD | WS_VISIBLE,
			10, 10,
			200, 30,
			hwnd, (HMENU)IDC_STATIC,
			NULL, NULL
		);
		HWND hCombo = CreateWindowEx
		(
			NULL, "ComboBox", "",
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
			10, 25,
			200, 200,
			hwnd, (HMENU)IDC_COMBO,
			NULL, NULL
		);
		HWND hButton = CreateWindowEx
		(
			NULL, "Button", "Применить",
			WS_CHILD | WS_VISIBLE,
			110, 50,
			100, 28,
			hwnd, (HMENU)IDC_BUTTON,
			NULL, NULL
		);

		CHAR sz_current_dir[MAX_PATH]{};
		std::string path = "";
		GetCurrentDirectory(MAX_PATH, sz_current_dir);
		path += sz_current_dir;
		path += "\\starcraft\\*";

		WIN32_FIND_DATA file_data;
		HANDLE hFile = FindFirstFile(path.c_str(), &file_data);
		std::vector<std::string> buf;
		for (
			HANDLE hFind = FindFirstFile(path.c_str(), &file_data);
			FindNextFile(hFind, &file_data);
			)
		{
			std::string tmp = file_data.cFileName;
			int index = tmp.find_first_of(".");
			if ((tmp.compare(index, 4, ".cur") == 0) || (tmp.compare(index, 4, ".ani") == 0))
				buf.push_back(file_data.cFileName);
		}
		for (size_t i = 0; i < buf.size(); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)buf[i].c_str());
		}

		FindClose(hFile);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParan))
		{
		case IDC_BUTTON:
		{
#ifdef Text_Element
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			HWND hStaticText = GetDlgItem(hwnd, IDC_STATIC_TEXT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hStaticText, WM_SETTEXT, 0, (LPARAM)sz_buffer);

#endif // Text_Element

			HCURSOR hC = LoadCursorFromFile((LPSTR)dir_way(hwnd).c_str());
			set_cursor(hwnd, hC);
			change_cursor = true;
		}
		break;
		default:
			break;
		}
	}
	break;
	case WM_SETCURSOR:
	{
		if (change_cursor == true)
		{
			HCURSOR hC = LoadCursorFromFile((LPSTR)dir_way(hwnd).c_str());
			set_cursor(hwnd, hC);
		}
		return TRUE;
	}
	break;
	case WM_SIZE:
	case WM_MOVE:
	case WM_ENTERSIZEMOVE:
	{
		size_screen_now(hwnd);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		//switch (MessageBox(hwnd,"Вы действительно хотите выйти?","Выход",MB_YESNOCANCEL|MB_ICONQUESTION))
		//{
		//case IDYES:
		//	//MessageBox(hwnd, "Пока", "Info", MB_OK);
		//	DestroyWindow(hwnd);
		//	break;
		//case IDNO:
		//	break;
		//default:
		//	break;
		//}
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParan, lParam);
		break;
	}
}

void size_screen_now(HWND& hwnd)
{
	RECT window_now;
	GetWindowRect(hwnd, &window_now);
	std::string buffer;
	buffer += std::to_string(window_now.right - window_now.left);
	buffer += " X ";
	buffer += std::to_string(window_now.bottom - window_now.top);
	SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer.c_str());
}

void set_cursor(HWND& hwnd, HCURSOR& hCursor)
{
	SetCursor(hCursor);
	SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
}

std::string dir_way(HWND& hwnd)
{
	HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
	int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
	CHAR sz_selected_cursor[_MAX_FNAME]{};
	SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_selected_cursor);

	CHAR sz_current_dir[MAX_PATH]{};
	std::string path = "";
	GetCurrentDirectory(MAX_PATH, sz_current_dir);
	path += sz_current_dir;
	path += "\\starcraft\\";
	path += sz_selected_cursor;
	//HCURSOR hCursor = (HCURSOR)LoadImage(NULL, "C:\\Users\\roman\\source\\repos\\Win_forms\\Winforms\\MainWindow\\starcraft\\Busy.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	return path;
}
