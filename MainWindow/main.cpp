//MainWindow
#include <Windows.h>
#include<cstdio>
#include "resource.h"

#define IDC_BUTTON 1000

CONST CHAR g_sz_WINDOW_CLASS[] = "My first window";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
    // 1. Регистрация класса окна. На этом этапе класс нашего окна регистрируется в ОС.
	// Класс окна это самая обычная строка с именем класса.
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	// Инициализируем размеры и стиль класса:
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass); //cb_ - Count Byte - количество байт;
	wClass.cbClsExtra = 0;  //Доолнительные бфйты класса.
	wClass.cbWndExtra = 0;

	// Инициализируем внешний вид окон:
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_BITCOIN));
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_PALM));
	//wClass.hIcon = (HICON)LoadImage(hInstance, "bitcoin.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = (HICON)LoadImage(hInstance, "palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance, 
		"gi\\gi_link.cur",
		IMAGE_CURSOR,
		LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);
	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	//Инициализация системных переменных:
	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration faild", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
    // 2. Создание окна.
	int screen_width = GetSystemMetrics(SM_CXSCREEN); //Размер экрана.
	int screen_height = GetSystemMetrics(SM_CYSCREEN); //Размер экрана.
	int window_width = screen_width * 3 / 4;
	int window_height = screen_height * 3 / 4;
	int x_position = screen_width / 8;
	int y_position = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		NULL,  //exStyle - дополнительные стили.
		g_sz_WINDOW_CLASS,  // Имя класса окна.
		g_sz_WINDOW_CLASS,  // Заголовок окна.
		WS_OVERLAPPEDWINDOW,//Стиль окна. Стили всезда зависят от класса окна.WS_OVERLAPPEDWINDOW - главное окно.
		x_position, y_position, //Position - начальная позиция.
		window_width, window_height, //Размер окна.
		NULL, // Наличие родителького окна.
		NULL, // Для главного окна это ResourceID главного меню, для дочернего окна (Control) это ResourceID 
		//дочернего окна, наример (IDC_BUTTON_COPY).
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Windows creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); // Создает режим отображения окна, например,"Развернуто на весь экран",
	                            // "Свернуто в окно", "Свернуто на ппанель задач.
	UpdateWindow(hwnd);         // Обновляет рабочую область окна отправляя сообщение WM_PAINT, 
	                            // если рабочая область окна не пустая.

	// 3. Запуск цикла сообщений.
	MSG(msg); //https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-msg
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg); // Преобразует сообщения виртуальных клавиш в символьные сообщения.
		DispatchMessage(&msg);  // Отравляет сообщение в процедуру окна.
	}
	
	return msg.wParam; //https://learn.microsoft.com/en-us/windows/win32/winmsg/using-messages-and-message-queues
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hButton = CreateWindowEx
		(
			NULL,                   //exStyle
			"Button",               //Class
			"Кнопка",               //Title
			WS_CHILD | WS_VISIBLE,  //Style
			10, 10,                 //Position
			150, 80,                //Size
			hwnd,                   //Parent
			(HMENU)IDC_BUTTON,     //Для главного окна это ResourceID главного меню, для дочернего окна (элемента)
		//управления окна 'Control') это ResourceID дочернего окна, наример (IDC_BUTTON_COPY).
			GetModuleHandle(NULL), //hInstence
			NULL                   //???
		);
	}
		break;
	case WM_MOVE: //сообщение об изменении положения окна на экране
	case WM_SIZE: // сообщение от изменении размера окна
	{
		RECT window_rect = {};  //функция, оределяющая рямоугольник окна
		GetWindowRect(hwnd, &window_rect);
		CONST INT SIZE = 256;
		CHAR sz_title[SIZE] = {}; //создаем буфер
		wsprintf
		(
			sz_title,
			"%s, Position: %ix%i, Size: %ix%i", // загоняем сюда информацию о прямоугольнике
			g_sz_WINDOW_CLASS,
			window_rect.left, window_rect.top, // позиция
			window_rect.right - window_rect.left,
			window_rect.bottom - window_rect.top //размеры окна

		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
			MessageBox(hwnd, "Cursor check", "Info", MB_OK | MB_ICONINFORMATION);
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
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}