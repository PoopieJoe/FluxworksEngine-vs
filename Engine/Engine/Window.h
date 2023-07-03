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

class FluxworksEngineWindow
{
public:
	class WindowClass
	{
	public:
		WindowClass();
		~WindowClass();
		//delete copy constructors
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;

		static const char* GetName(void);
		static HINSTANCE GetInstance(void);
		static WindowClass wndClass;

	private:
		static constexpr const char* wndClassName = "FluxworksEngineWindow";
		
		HINSTANCE hInst;

	};

public:
	FluxworksEngineWindow(int width, int height, const char* name, std::shared_ptr<FluxworksEventDispatcher> eventDispatcher);
	~FluxworksEngineWindow();
	//delete copy constructors
	FluxworksEngineWindow(const FluxworksEngineWindow&) = delete;
	FluxworksEngineWindow& operator=(const FluxworksEngineWindow&) = delete;
private:
	static LRESULT CALLBACK HandeMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandeMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	std::shared_ptr<FluxworksEventDispatcher> evd;
	int width;
	int height;
	HWND hWnd;
	WindowClass cls;
};