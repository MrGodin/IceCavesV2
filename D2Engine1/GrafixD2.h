
#pragma once
#include "UtilsD2.h"
#include "SpriteSheetImage.h"
#include "Texture.h"
#include "RenderTarget.h"
#include "D2D.h"

class GrafixD2 : public RenderTarget
{
	D2D &d2d;
	D2D1::Matrix3x2F matID;

public:
	GrafixD2(D2D &d2d);
	~GrafixD2();
	
	HRESULT StartFrame();
	HRESULT EndFrame();

	void Rasterize(Drawable& obj)override;

	void DrawLine(Point2F start, Point2F end, D2Brush brush, float width);
	void DrawBitmap(D2Bitmap image, D2Brush brush, RECT rect, float X, float Y);
	void DrawRectangle(D2D1_RECT_F rect, D2Brush brush);	
	void DrawSprite(D2D1_MATRIX_3X2_F &trans, D2D1_RECT_F &PosSize, ID2D1Bitmap *pSprite,
		D2D1_BITMAP_PROPERTIES bp, float Opacity = 1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE InterpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1_RECT_F *ClipRect = nullptr);
	void RenderText(LPWSTR String, IDWriteTextFormat *pFormat,
		const D2D1_RECT_F &DrawRect, D2D1_COLOR_F &Color);
}; 