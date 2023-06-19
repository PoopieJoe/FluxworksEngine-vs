#pragma once
#include <Windows.h>
#include <windowsx.h>

LRESULT CALLBACK WindowProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
);

//class WindowRenderer
//{
//
//};