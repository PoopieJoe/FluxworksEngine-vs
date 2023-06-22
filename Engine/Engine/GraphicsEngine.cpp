#include "pch.h"
#include "GraphicsEngine.h"

#include <thread>
#include <iostream>

// Windows Header Files
#include "WindowsIncludes.h"
#include <windowsx.h>

// Microsoft Header
#include <wrl.h>  

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

static Direct3D11API dx3dapi = Direct3D11API();

MainWindow::MainWindow(std::shared_ptr<FluxworksEventDispatcher> evd, const wchar_t* title)
{
    this->evd = evd;
    this->title = title;
    WNDCLASSEX wc = {0};

    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL));
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = L"FluxworksEngineWindow";
    wc.hIcon = NULL;

    RegisterClassEx(&wc);

    assert(!m_window);

    CreateWindow(
        wc.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        200, 200, //(x,y)
        480, 360, //(w,h)
        nullptr,
        nullptr,
        wc.hInstance,
        this
    );

    assert(m_window);
}

LRESULT MainWindow::MessageHandler(
    UINT message,
    WPARAM const wparam,
    LPARAM const lparam
) {
    static WindowsMessageMap wmm; // message map for debug
    if (message != WM_PAINT) std::cout << wmm(message, wparam, lparam).c_str() << std::endl;

    switch (message)
    {
    case WM_PAINT:
    {
        PaintHandler();
        return 0;
    }
    case WM_KEYDOWN:
    {
        this->evd->dispatchEvent(new KeyDown(wparam,lparam >> 29));
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        InputModifiers mod = InputModifiers(
            wparam & MK_LBUTTON,
            wparam & MK_MBUTTON,
            wparam & MK_RBUTTON,
            wparam & MK_CONTROL,
            wparam & MK_SHIFT,
            false,
            wparam & MK_XBUTTON1,
            wparam & MK_XBUTTON2
        );

        this->evd->dispatchEvent(new MouseButtonDown(MouseButton::LeftMouseButton, mod, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
        return 0;
    }
    case WM_MBUTTONDOWN:
    {
        InputModifiers mod = InputModifiers(
            wparam & MK_LBUTTON,
            wparam & MK_MBUTTON,
            wparam & MK_RBUTTON,
            wparam & MK_CONTROL,
            wparam & MK_SHIFT,
            false,
            wparam & MK_XBUTTON1,
            wparam & MK_XBUTTON2
        );

        this->evd->dispatchEvent(new MouseButtonDown(MouseButton::MiddleMouseButton, mod, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
        return 0;
    }
    case WM_RBUTTONDOWN:
    {
        InputModifiers mod = InputModifiers(
            wparam & MK_LBUTTON,
            wparam & MK_MBUTTON,
            wparam & MK_RBUTTON,
            wparam & MK_CONTROL,
            wparam & MK_SHIFT,
            false,
            wparam & MK_XBUTTON1,
            wparam & MK_XBUTTON2
        );

        this->evd->dispatchEvent(new MouseButtonDown(MouseButton::RightMouseButton, mod, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
        return 0;
    }
    case WM_CREATE:
    {
        this->evd->dispatchEvent(new Open(this->m_window));
        return 0;
    }
    case WM_CLOSE:
    {
        this->evd->dispatchEvent(new Close(this->m_window));
        return 0;
    }
    case WM_MOUSEMOVE:
    {
        InputModifiers mod = InputModifiers(
            wparam & MK_LBUTTON,
            wparam & MK_MBUTTON,
            wparam & MK_RBUTTON,
            wparam & MK_CONTROL,
            wparam & MK_SHIFT,
            false,
            wparam & MK_XBUTTON1,
            wparam & MK_XBUTTON2
        );
        this->evd->dispatchEvent(new MouseMove(mod, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
        return 0;
    }
    }
    return __super::MessageHandler(
        message,
        wparam,
        lparam
    );
}

void MainWindow::PaintHandler()
{
    // Render . . .
}

template <typename T>
T* Window<T>::GetThisFromHandle(HWND window)
{
    return reinterpret_cast<T*>(
        GetWindowLongPtr(
            window,
            GWLP_USERDATA
        )
    );
}

template <typename T>
LRESULT CALLBACK Window<T>::WndProc
(
    HWND   const window,
    UINT   const message,
    WPARAM const wparam,
    LPARAM const lparam
) {
    assert(window);

    if (WM_NCCREATE == message)
    {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lparam);
        T* that = static_cast<T*>(cs->lpCreateParams);

        assert(that);
        assert(!that->m_window);

        that->m_window = window;

        SetWindowLongPtr(
            window,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(that)
        );
    }
    else if (T* that = GetThisFromHandle(window))
    {
        return that->MessageHandler(
            message,
            wparam,
            lparam
        );
    }

    return DefWindowProc(
        window,
        message,
        wparam,
        lparam
    );
}

template <typename T>
LRESULT Window<T>::MessageHandler(
    UINT   const message,
    WPARAM const wparam,
    LPARAM const lparam
) {
    if (WM_DESTROY == message)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(
        this->m_window,
        message,
        wparam,
        lparam
    );
}