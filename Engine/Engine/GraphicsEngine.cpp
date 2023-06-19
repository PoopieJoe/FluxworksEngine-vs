#include "pch.h"
#include "GraphicsEngine.h"

#include <thread>
#include <iostream>

#include <Windows.h>
#include <windowsx.h>

#include "ErrorTypes.h"

WindowRenderer::WindowRenderer()
{
	this->_running = false;
	this->hwnd = NULL;
}

WindowRenderer::~WindowRenderer()
{
}

LRESULT WindowRenderer::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::cout << "WindowProc" << std::endl;
	switch (message)
	{
		case WM_DESTROY:
		{
			std::cout << "Quitting Window" << std::endl;
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void WindowRenderer::initializeWindow(void)
{
	this->wndclass.style = CS_HREDRAW | CS_VREDRAW;
	this->wndclass.cbClsExtra = 0;
	this->wndclass.cbWndExtra = 0;
	this->wndclass.lpszClassName = L"Window";
	this->wndclass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	this->wndclass.lpszMenuName = NULL;
	this->wndclass.lpfnWndProc = WindowRenderer::WindowProc;
	this->wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	this->wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	this->wndclass.hInstance = GetModuleHandle(NULL);


	if (RegisterClass(&(this->wndclass)))
	{
		this->hwnd = CreateWindowEx(
			WS_EX_LEFT,
			this->wndclass.lpszClassName, 
			L"AAA",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			100, 
			100, 
			350, 
			250,
			NULL, 
			NULL, 
			GetModuleHandle(NULL), 
			NULL
		);
	}
}

void WindowRenderer::createWindow(void)
{
	if (!this->_running)
	{
		this->_running = true;
		std::cout << "Create window" << std::endl;
		std::thread windowThread([this]()
		{
			ShowWindow(this->hwnd, SW_SHOWNORMAL);
			MSG msg;
			BOOL bRet;
			while (this->_running && this->hwnd)
			{
				bRet = GetMessage(&msg, this->hwnd, 0, 0);

				if (bRet > 0)  // (bRet > 0 indicates a message that must be processed.)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else if (bRet < 0)  // (bRet == -1 indicates an error.)
				{
					// Handle or log the error; possibly exit.
					// ...
					break;
				}
				else  // (bRet == 0 indicates "exit program".)
				{
					std::cout << "Window loessoe" << std::endl;
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
