#pragma once
#include "pch.h"

// C RunTime Header Files
#include <assert.h>
#include <memory>
#include <tchar.h>
#include <thread>
#include <iostream>

#include "EventDispatcher.h"
#include "GraphicsDriver.h"

class FluxworksEngineWindow
{
private:
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

	inline const uintptr_t identifier() {return reinterpret_cast<const uintptr_t>(this->hWnd);}
	const char* name;
	FluxworksGraphics& GFX();


private:
	FluxworksEngineWindow();
	static LRESULT CALLBACK HandeMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandeMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	std::shared_ptr<FluxworksEventDispatcher> evd;
	int width;
	int height;
	HWND hWnd;
	WindowClass cls;
	std::unique_ptr<FluxworksGraphics> gfx;
};