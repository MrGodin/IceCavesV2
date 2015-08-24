#include "Graphics.h"
#include "Game.h"

Graphics::Graphics(ID2D1SolidColorBrush* pBrush, ID2D1RenderTarget *pRT)
	:
	prt(pRT),
	pBrush(pBrush)
{
}


Graphics::~Graphics()
{
}


void Graphics::DrawSprite(D2D1_RECT_F &PosSize, ID2D1Bitmap *pSprite, 
	D2D1_BITMAP_PROPERTIES &bp, float Opacity, 
	D2D1_BITMAP_INTERPOLATION_MODE InterpMode,
	D2D1_RECT_F *ClipRect)
{
	prt->DrawBitmap(pSprite, PosSize, Opacity, InterpMode, ClipRect);
}

void Graphics::RenderText(LPWSTR String, IDWriteTextFormat *pFormat,
	const D2D1_RECT_F &DrawRect, D2D1_COLOR_F &Color)
{
	pBrush->SetColor(Color);
	UINT strLen = lstrlen(String);
	prt->DrawTextW(String, strLen, pFormat, DrawRect, pBrush);
}
