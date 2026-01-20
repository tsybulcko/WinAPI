#pragma once
#include <Windows.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "Calc PV_521";


CONST INT g_i_WINDOW_COLOR = 0;
CONST INT g_i_DISPLAY_COLOR = 1;
CONST INT g_i_FONT_COLOR = 2;
CONST COLORREF g_clr_COLORS[][3] =
{
	{RGB(0,0,150), RGB(0,0,100), RGB(250,0,0)}, // Цвет фона, цвет дисплея, цвет шрифта (для одной темы)
	{RGB(100,100,150), RGB(50,50,50), RGB(0,255,0)}, // Цвет фона, цвет дисплея, цвет шрифта (для другой темы)
};
CONST CHAR* g_sz_SKIN[] = { "Square_blue", "Metal_mistral" };

