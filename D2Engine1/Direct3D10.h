#pragma once
/*
Add all functions that pertain to Direct3D here such as creating 
ID3D10Texture2D *.
*/

// Test to see if Windows.h needs to be included
#ifndef _INC_WINDOWS
#include <Windows.h>
#endif

// Test to see if Direct3D 10 needs to be included
#ifndef __d3d10_1_h__
#include <d3d10_1.h>
#pragma comment(lib, "d3d10_1.lib")
#endif

class Direct3D10
{
public:
	Direct3D10(HWND WinHandle, UINT WindowWidth, UINT WindowHeight);
	~Direct3D10();

	IDXGISwapChain *GetSwapChain()const;
private:
	IDXGISwapChain *psc;
	ID3D10Device1 *pDevice;

	IDXGIDevice *pDxgiDevice;
	IDXGIAdapter *pAdapter;
	IDXGIFactory *pDxgiFactory;

	// Just in case device is lost I suppose
	DXGI_SWAP_CHAIN_DESC sd;
};

