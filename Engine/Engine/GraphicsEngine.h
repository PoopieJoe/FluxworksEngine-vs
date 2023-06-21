#pragma once

#include <thread>


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <windowsx.h>
#include <winnt.h>
// C RunTime Header Files
#include <assert.h>
#include <stdlib.h>
#include <memory>
#include <tchar.h>
#include <thread>
#include <iostream>

#include "EventDispatcher.h"


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

class LeftMouseButtonDownEvent : public FluxworksEvent
{
public:
	LeftMouseButtonDownEvent(long x, long y)
	{
		this->x = x;
		this->y = y;
	}

	long x;
	long y;
};

template <typename T>
struct Window
{
    HWND m_window = nullptr;

    static T* GetThisFromHandle(HWND window)
    {
        return reinterpret_cast<T*>(
            GetWindowLongPtr(
                window,
                GWLP_USERDATA
            )
        );
    }

    static LRESULT CALLBACK WndProc
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

    LRESULT MessageHandler(
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
            m_window,
            message,
            wparam,
            lparam
        );
    }
};

struct SampleWindow : Window<SampleWindow>
{
    std::shared_ptr<FluxworksEventDispatcher> evd;

    SampleWindow(std::shared_ptr<FluxworksEventDispatcher> evd)
    {
        this->evd = evd;
        WNDCLASS wc = {};

        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL));
        wc.lpszClassName = L"SampleWindow";
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;

        RegisterClass(&wc);

        assert(!m_window);

        CreateWindow(
            wc.lpszClassName,
            L"Window Title",
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

    LRESULT MessageHandler(
        UINT message,
        WPARAM const wparam,
        LPARAM const lparam
    ) {
        switch (message)
        {
            case WM_PAINT:
            {
                PaintHandler();
                return 0;
            }
            case WM_LBUTTONDOWN:
            {
                POINT p;
                p.x = GET_X_LPARAM(lparam);
                p.y = GET_Y_LPARAM(lparam);
                this->evd->dispatchEvent(new LeftMouseButtonDownEvent(p.x,p.y));
                return 0;
            }
        }
        return __super::MessageHandler(
            message,
            wparam,
            lparam
        );
    }

    void PaintHandler()
    {
        // Render . . .
    }
};