#include "pch.h"
#include "GraphicsEngine.h"

#include <Windows.h>
#include <windowsx.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	// Window handle
	HWND hWnd;

	// Window information
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Construct the wc
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	// register window
	RegisterClassEx(&wc);

	// Create window
	hWnd = CreateWindowEx(
		NULL,
		L"WindowClass1",
		L"Our First Windowed Program",
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		500,
		400,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// Display Window
	ShowWindow(hWnd, nCmdShow);

	// Window event loop
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}