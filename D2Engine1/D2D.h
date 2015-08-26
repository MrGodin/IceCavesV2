#pragma once

#include "UtilsD2.h"

#pragma comment(lib, "d2d1.lib")

class D2D
{
public:
	D2D(HWND WinHandle);
	~D2D();

	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	// Release device-dependent resource.
	void DiscardDeviceResources();

	// Resize the render target.
	void OnResize(UINT width, UINT height);
	D2D1_POINT_2F GetDpi() const;
	D2D1_POINT_2U &WindowSize() { return windowSize; }

	ID2D1HwndRenderTarget *GetRT() { return m_pRenderTarget; }
	ID2D1SolidColorBrush* GetSolidBrush()const;
private:
	ID2D1HwndRenderTarget *m_pRenderTarget = nullptr;
	ID2D1Factory* m_pDirect2dFactory = nullptr;
	ID2D1SolidColorBrush* m_pWhiteBrush = nullptr;

	HWND m_hwnd;
	D2D1_POINT_2U windowSize;
};