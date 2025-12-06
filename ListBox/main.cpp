#include<Windows.h>
#include"resource.h"


CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "firse", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdSow)
{
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
			EndDialog(hwnd, 0);
		}
	}
	break;
	case WM_CLOSE:
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