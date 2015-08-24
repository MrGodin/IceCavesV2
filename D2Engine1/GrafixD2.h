
#pragma once
#include "UtilsD2.h"
#include "SpriteSheetImage.h"
#include "Texture.h"
#include "RenderTarget.h"
//extern ID2D1HwndRenderTarget *m_pRenderTarget;
extern LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
	);


class GrafixD2 : public RenderTarget
{
private:
	bool initialized = false;
	D2D1::Matrix3x2F matID;
	SpriteSheetImage TileImages1;
	ID2D1HwndRenderTarget *m_pRenderTarget = nullptr;
public:

	GrafixD2();
	~GrafixD2();

	// Register the window class and call methods for instantiating drawing resources
	HRESULT Initialize();
	
	
	// Process and dispatch messages
	
	HRESULT StartFrame();
	HRESULT EndFrame();
	// get render target
	virtual void Rasterize(Drawable& obj)override;
	ID2D1HwndRenderTarget *GetRT() { return m_pRenderTarget; }
	void DrawLine(Point2F start, Point2F end, D2Brush brush, float width);
	void DrawBitmap(D2Bitmap image, D2Brush brush, RECT rect, float X, float Y);
	void DrawRectangle(D2D1_RECT_F rect, D2Brush brush);
	
	void DrawSprite(D2D1_RECT_F &PosSize, ID2D1Bitmap *pSprite,
		D2D1_BITMAP_PROPERTIES bp, float Opacity = 1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE InterpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1_RECT_F *ClipRect = nullptr);
	void RenderText(LPWSTR String, IDWriteTextFormat *pFormat,
		const D2D1_RECT_F &DrawRect, D2D1_COLOR_F &Color);
	// Resize the render target.
	void OnResize(UINT width,UINT height);
	uint2 WindowSize() { return windowSize; }
private:
	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	// Release device-dependent resource.
	void DiscardDeviceResources();

	// Draw content.
	

	
private:
	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1SolidColorBrush* m_pWhiteBrush = nullptr;
	uint2 windowSize;
	
}; 