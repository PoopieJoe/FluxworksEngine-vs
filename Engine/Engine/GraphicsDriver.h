#pragma once
#include "pch.h"
#include <d3d11.h>


class FLUXWORKSENGINE_API FluxworksGraphics
{
public:
	FluxworksGraphics( HWND hWnd );
	~FluxworksGraphics();

	//delete copy constructors
	FluxworksGraphics& operator=(const FluxworksGraphics&) = delete;
	FluxworksGraphics(const FluxworksGraphics&) = delete;

	void present();
	void clear(float r, float g, float b, float a);

private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
};