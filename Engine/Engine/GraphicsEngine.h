#pragma once

#include <thread>


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_VSENGINEPROJECT_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_VSENGINEPROJECT			107
#define IDI_SMALL				108
#define IDC_VSENGINEPROJECT			109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif

class WindowRenderer {
	bool _running;
	WNDCLASSEX wndclass;
	HWND hwnd;
	HACCEL hAccelTable;
	INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

public:
	WindowRenderer();
	~WindowRenderer();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void initializeWindow( void );
	void createWindow(void);
};