#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"


CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "firse", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID SaveList(HWND hwnd, CONST CHAR filename[]);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdSow)
{
	//hInstance - это экземляр иполняемого файла программы, загруженного в память(*.exe)
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
			if (HIWORD(wParam) == LBN_DBLCLK)
				// GetModuleHandle(NULL) - возвращает 'hInstance' нашей программы.
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcEdit, 0);
			break;
		case IDC_BUTTON_ADD:
		{
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
		}
			break;
		case IDC_BUTTON_DELETE:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_DELETESTRING, i, 0);
		}
		break;
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{}; //sz_ - String Zero (NULL Terminated Line)
			CHAR sz_message[SIZE]{};//Мессадж, который будет выводиться в МессаджБокс.
			
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0); //GetCurrentSelection - Получить текущий выбранный элемент.

			if (i != LB_ERR)
			{
				SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer); // Прочитать выбранный элемент.
				wsprintf(sz_message, "Вы выбрали элемент %i со значением \"%s\".", i, sz_buffer);
				// wsprintf - вставляет в строку переменные значения.
				// sprintf - вставляет в строку переменные значения, но нужно подключить _CRT_SECURE_NO_WARNINGS.
				MessageBox(hwnd, sz_message, "info", MB_OK | MB_ICONINFORMATION); //Вывод текста на экран.
			}
			else
			{
				MessageBox(hwnd, "Вы ничего не выбрали", "info", MB_OK | MB_ICONINFORMATION);
			}
		}
			break;
		case IDCANCEL:
			SaveList(hwnd, "List.txt");
			EndDialog(hwnd, 0);
		}
	}
	break;
	case WM_CLOSE:
		SaveList(hwnd, "List.txt");
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SetFocus(GetDlgItem(hwnd, IDC_EDIT));
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			HWND hParent = GetParent(hwnd);
			HWND hList = GetDlgItem(hParent, IDC_LIST1);
			if (SendMessage(hList, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_buffer) == LB_ERR)
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			else
			{
				MessageBox(hwnd, "Такой элемент уже существует", "Warning", MB_OK | MB_ICONWARNING);
				break;
			}
		}
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CONST INT SIZE = 256;
	CHAR sz_buffer[SIZE] = {};
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"Изменить");
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		HWND hParent = GetParent(hwnd);
		HWND hList = GetDlgItem(hParent, IDC_LIST1);
		INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
		SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		SetFocus(hEdit);
		SendMessage(hEdit, EM_SETSEL, strlen(sz_buffer), -1);

	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			HWND hParent = GetParent(hwnd);
			HWND hList = GetDlgItem(hParent, IDC_LIST1);
			INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (SendMessage(hList, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_buffer) == LB_ERR);
			{
				SendMessage(hList, LB_DELETESTRING, i, NULL);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			}
		}
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;	
}
VOID SaveList(HWND hwnd, CONST CHAR filename[])
{
	CONST INT SIZE = 32768;
	CHAR sz_buffer[SIZE] = {};

	HWND hList = GetDlgItem(hwnd, IDC_LIST1);
	INT n = SendMessage(hList, LB_GETCOUNT, 0, 0);

	for (int i = 0; i < n; i++)
	{
		CHAR sz_item[256] = {};
		SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_item);
		strcat(sz_buffer, sz_item);
		strcat(sz_buffer, "\n");
		/*
		strcat(sz_buffer, sz_item);
		strcat(sz_buffer, "\n");
		*/
	}

	HANDLE hFile = CreateFile
	(
		filename,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	DWORD dwBytesWritten = 0;
	WriteFile(hFile, sz_buffer, strlen(sz_buffer), &dwBytesWritten, NULL);
	CloseHandle(hFile);
}