#pragma once

#include <thread>


#include <Windows.h>
#include <windowsx.h>

class WindowRenderer {
	bool _running;
	WNDCLASS wndclass;
	HWND hwnd;

public:
	WindowRenderer();
	~WindowRenderer();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void initializeWindow( void );
	void createWindow(void);
};