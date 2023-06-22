#include "pch.h"
#include "GraphicsEngine.h"

#include <thread>
#include <iostream>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
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
#include "EventDispatcher.h"

static Direct3D11API dx3dapi = Direct3D11API();

MainWindow::MainWindow(std::shared_ptr<FluxworksEventDispatcher> evd, const wchar_t* title)
{
    this->evd = evd;
    this->title = title;
    WNDCLASS wc = {0};

    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL));
    wc.hbrBackground = NULL;
    wc.lpszClassName = L"FluxworksEngineWindow";
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.hIcon = NULL;

    RegisterClass(&wc);

    assert(!m_window);

    CreateWindow(
        wc.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
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
    std::cout << wmm(message, wparam, lparam).c_str() << std::endl;


    switch (message)
    {
    case WM_PAINT:
    {
        PaintHandler();
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        this->evd->dispatchEvent(new WindowEvents::Mouse::LMBDown(this->m_window, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
        return 0;
    }
    case WM_CREATE:
    {
        this->evd->dispatchEvent(new WindowEvents::Open(this->m_window));
        return 0;
    }
    case WM_CLOSE:
    {
        this->evd->dispatchEvent(new WindowEvents::Close(this->m_window));
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