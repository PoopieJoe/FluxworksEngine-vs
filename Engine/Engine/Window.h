#pragma once
#include "pch.h"

#include <thread>

// DirectX 3D 11
#include <d3d11.h>
#include <d3d11_2.h>

// C RunTime Header Files
#include <assert.h>
#include <memory>
#include <tchar.h>
#include <thread>
#include <iostream>

#include "EventDispatcher.h"
#include "EventTypes.h"


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



// Create the Direct3D 11 API device object and a corresponding context.
struct Direct3D11API {
    Microsoft::WRL::ComPtr<ID3D11Device>        device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
};

template <typename T>
struct Window
{
    HWND m_window = nullptr;

    static T* GetThisFromHandle(HWND window);

    static LRESULT CALLBACK WndProc
    (
        HWND   const window,
        UINT   const message,
        WPARAM const wparam,
        LPARAM const lparam
    );

    LRESULT MessageHandler(
        UINT   const message,
        WPARAM const wparam,
        LPARAM const lparam
    );
};

struct MainWindow : Window<MainWindow>
{
    std::shared_ptr<FluxworksEventDispatcher> evd;
    const wchar_t* title;



    MainWindow(std::shared_ptr<FluxworksEventDispatcher> evd, const wchar_t* title);

    LRESULT MessageHandler(
        UINT message,
        WPARAM const wparam,
        LPARAM const lparam
    );

    void PaintHandler();
};