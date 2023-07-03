#include "pch.h"
#include "Window.h"

#include <thread>
#include <iostream>

// DirectX 3D 11
#include <d3d11.h>
#include <d3d11_2.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "WindowsMessageMap.h"

#include "ErrorTypes.h"
#include "EventTypes.h"
#include "EventDispatcher.h"

FluxworksEngineWindow::WindowClass FluxworksEngineWindow::WindowClass::wndClass;

const char* FluxworksEngineWindow::WindowClass::GetName(void)
{
	return wndClassName;
}

HINSTANCE FluxworksEngineWindow::WindowClass::GetInstance(void)
{
	return wndClass.hInst;
}

FluxworksEngineWindow::WindowClass::WindowClass()
	: hInst ( GetModuleHandle( NULL ) )
{
	WNDCLASSEX wc = { NULL }; // zero out config
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandeMsgSetup;
	wc.cbClsExtra = 0; // no extra bytes allocated for window class
	wc.cbWndExtra = 0; // no extra bytes allocated for window instance
	wc.hInstance = GetInstance();
	wc.hIcon = NULL;
	wc.hCursor = nullptr;// LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"FluxworksEngineWindow";//WindowClass::GetName();
	wc.hIconSm = NULL;

	RegisterClassEx( &wc );
}

FluxworksEngineWindow::WindowClass::~WindowClass()
{
	UnregisterClassA(wndClassName, GetInstance());
}

FluxworksEngineWindow::FluxworksEngineWindow(int width, int height, const char* name, std::shared_ptr<FluxworksEventDispatcher> eventDispatcher)
	: width( width ), height( height ), evd(eventDispatcher)
{
	const DWORD windowStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
	RECT windowRegion;
	windowRegion.left = 100;
	windowRegion.right = width + windowRegion.left;
	windowRegion.top = 100;
	windowRegion.bottom = height + windowRegion.top;
	if (AdjustWindowRect(&windowRegion, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw std::runtime_error("Invalid Window Region");
	}
	hWnd = CreateWindowExA(WS_EX_LEFT,
		WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, windowRegion.right - windowRegion.left, windowRegion.bottom - windowRegion.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);
	if (hWnd == NULL)
	{
		throw std::runtime_error("Invalid Window Handler");
	}
	ShowWindow(hWnd, SW_SHOWDEFAULT);

}

FluxworksEngineWindow::~FluxworksEngineWindow()
{
	DestroyWindow(hWnd);
}

LRESULT CALLBACK FluxworksEngineWindow::HandeMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		// reinterpret lParam to the window creation data struct
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		// fetch pointer to FluxworksEngineWindow instance from creation data
		FluxworksEngineWindow* const pWnd = static_cast<FluxworksEngineWindow*>(pCreate->lpCreateParams);
		// set the user data associated with the window
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// change static window handle function to HandeMsgThunk
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&FluxworksEngineWindow::HandeMsgThunk));
		// Forward message to instance handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK FluxworksEngineWindow::HandeMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// this cursed line fetches the pointer to the window instance
	FluxworksEngineWindow* const pWnd = 
		reinterpret_cast<FluxworksEngineWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// Now forward it to the window instance handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT FluxworksEngineWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Window-specific message handling
    //static WindowsMessageMap wmm; // message map for debug
    //if (msg != WM_PAINT) std::cout << wmm(msg, wParam, lParam).c_str() << std::endl;

    switch (msg)
    {
        case WM_PAINT:
        {
            break;
        }
        case WM_KEYDOWN:
        {
            this->evd->dispatchEvent(new KeyDown(wParam, lParam >> 29), false);
            return 0;
        }
        case WM_LBUTTONDOWN:
        {
            InputModifiers mod = InputModifiers(
                wParam & MK_LBUTTON,
                wParam & MK_MBUTTON,
                wParam & MK_RBUTTON,
                wParam & MK_CONTROL,
                wParam & MK_SHIFT,
                false,
                wParam & MK_XBUTTON1,
                wParam & MK_XBUTTON2
            );

            this->evd->dispatchEvent(new MouseButtonDown(MouseButton::LeftMouseButton, mod, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), false);
            return 0;
        }
        case WM_MBUTTONDOWN:
        {
            InputModifiers mod = InputModifiers(
                wParam & MK_LBUTTON,
                wParam & MK_MBUTTON,
                wParam & MK_RBUTTON,
                wParam & MK_CONTROL,
                wParam & MK_SHIFT,
                false,
                wParam & MK_XBUTTON1,
                wParam & MK_XBUTTON2
            );

            this->evd->dispatchEvent(new MouseButtonDown(MouseButton::MiddleMouseButton, mod, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), false);
            return 0;
        }
        case WM_RBUTTONDOWN:
        {
            InputModifiers mod = InputModifiers(
                wParam & MK_LBUTTON,
                wParam & MK_MBUTTON,
                wParam & MK_RBUTTON,
                wParam & MK_CONTROL,
                wParam & MK_SHIFT,
                false,
                wParam & MK_XBUTTON1,
                wParam & MK_XBUTTON2
            );

            this->evd->dispatchEvent(new MouseButtonDown(MouseButton::RightMouseButton, mod, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), false);
            return 0;
        }
        case WM_CREATE:
        {
            this->evd->dispatchEvent(new Open(this->hWnd), false);
            return 0;
        }
        case WM_CLOSE:
        {
            this->evd->dispatchEvent(new Close(this->hWnd), false);
            return 0;
        }
        case WM_MOUSEMOVE:
        {
            InputModifiers mod = InputModifiers(
                wParam & MK_LBUTTON,
                wParam & MK_MBUTTON,
                wParam & MK_RBUTTON,
                wParam & MK_CONTROL,
                wParam & MK_SHIFT,
                false,
                wParam & MK_XBUTTON1,
                wParam & MK_XBUTTON2
            );
            this->evd->dispatchEvent(new MouseMove(mod, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), false);
            return 0;
        }
    }

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

