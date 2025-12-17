//MainWindow
#include <Windows.h>

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
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	//Инициализация системных переменныч:
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
	HWND hwnd = CreateWindowEx
	(
		NULL,  //exStyle - дополнительные стили.
		g_sz_WINDOW_CLASS,  // Имя класса окна.
		g_sz_WINDOW_CLASS,  // Заголовок окна.
		WS_OVERLAPPEDWINDOW,//Стиль окна. Стили всезда зависят от класса окна.WS_OVERLAPPEDWINDOW - главное окно.
		CW_USEDEFAULT, CW_USEDEFAULT, //Position - начальная позиция.
		CW_USEDEFAULT, CW_USEDEFAULT, //Размер окна.
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
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 3. Запуск цикла сообщений.
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
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