#include "pch.h"
#include "GraphicsEngine.h"

#include <thread>
#include <iostream>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <windowsx.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "ErrorTypes.h"
#include "EventDispatcher.h"

WindowRenderer::WindowRenderer()
{
	this->_running = false;
	this->hwnd = NULL;
	this->hAccelTable = HACCEL();
	this->windowTitle = L"";
	this->wndclass = WNDCLASSEX();
}

WindowRenderer::~WindowRenderer()
{
}

void WindowRenderer::initializeWindow(const wchar_t* title)
{
	this->windowTitle = title;

	this->wndclass.cbSize = sizeof(WNDCLASSEX);

	this->wndclass.style = CS_HREDRAW | CS_VREDRAW;
	this->wndclass.lpfnWndProc = WindowRenderer::WindowProc;
	this->wndclass.cbClsExtra = 0;
	this->wndclass.cbWndExtra = 0;
	this->wndclass.hInstance = GetModuleHandle(NULL);
	this->wndclass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_VSENGINEPROJECT));
	this->wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	this->wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	this->wndclass.lpszMenuName = MAKEINTRESOURCEW(IDC_VSENGINEPROJECT);
	this->wndclass.lpszClassName = this->windowTitle;
	this->wndclass.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SMALL));
}

void WindowRenderer::createWindow(const wchar_t* title, windowEventCallback_t callback)
{
	if (!this->_running)
	{
		this->_running = true;
		this->windowTitle = title;
		//WindowRenderer::windowEventCallback = callback;
		this->initializeWindow(this->windowTitle);
		this->hAccelTable = LoadAccelerators(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_VSENGINEPROJECT));

		std::thread windowThread([this]()
		{
			if (RegisterClassEx(&(this->wndclass)))
			{
				this->hwnd = CreateWindowW(
					this->wndclass.lpszClassName,
					this->windowTitle,
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,
					0, 
					CW_USEDEFAULT,
					0,
					nullptr,
					nullptr,
					GetModuleHandle(NULL),
					nullptr
				);
				ShowWindow(this->hwnd, SW_SHOWNORMAL);
				UpdateWindow(this->hwnd);
				std::cout << "Window opened" << std::endl;
			}

			MSG msg;
			BOOL bRet;
			while (this->_running && this->hwnd)
			{
				bRet = GetMessage(&msg, this->hwnd, 0, 0);
				if (bRet > 0)  // (bret > 0 indicates a message that must be processed.)
				{
					if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
				else if (bRet < 0)  // (bret == -1 indicates an error.)
				{
					// handle or log the error; possibly exit.
					// ...
					break;
				}
				else  // (bret == 0 indicates "exit program".)
				{
					std::cout << "window loessoe" << std::endl;
					break;
				}
			}
		});
		windowThread.detach();
		return;
	}
	else
	{
		throw FluxworksWindowAlreadyOpenException("Fluxworks Engine window is already open");
	}
}


LRESULT WindowRenderer::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
					DialogBoxParam(GetModuleHandleW(0), ((LPWSTR)((ULONG_PTR)((WORD)(103)))), hWnd, WindowRenderer::About, 0L);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			std::cout << "Window destroyed" << std::endl;
			PostQuitMessage(0);
			break;

		case WM_LBUTTONDOWN:
			POINT p;
			p.x = GET_X_LPARAM(lParam);
			p.y = GET_Y_LPARAM(lParam);
			std::cout << "WM_LBUTTONDOWN (" << p.x << "," << p.y << ")" << std::endl;
			//WindowRenderer::windowEventCallback(new LeftMouseButtonDownEvent(p.x,p.y));

		default:
			//std::cout << "Window message: " << std::hex << message << std::endl;
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK WindowRenderer::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
