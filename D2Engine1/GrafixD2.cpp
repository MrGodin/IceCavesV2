#include "GrafixD2.h"

GrafixD2::GrafixD2(D2D &d2d)
	:
	d2d(d2d)
{
}

GrafixD2::~GrafixD2()
{
}

void GrafixD2::Rasterize(Drawable& obj)
{
	 obj.Rasterize(*this);
}

//=============================================================================
void GrafixD2::DrawLine(Point2F start, Point2F end, D2Brush brush, float lineWidth)
{
	ID2D1SolidColorBrush *pBrush = d2d.GetSolidBrush();
	pBrush->SetColor({ 0.0f,0.0f,1.0f,1.0f });

	d2d.GetRT()->DrawLine(
		D2D1::Point2F(start.x, start.y),
		D2D1::Point2F(end.x, end.y),
		pBrush,
		lineWidth
		);
};
//==============================================================================
void GrafixD2::DrawRectangle(D2D1_RECT_F rect, D2Brush brush)
{
	d2d.GetRT()->FillRectangle(&rect, brush);
}
void GrafixD2::DrawBitmap(D2Bitmap image, D2Brush brush,RECT rect, float X, float Y)
{
	ID2D1SolidColorBrush *pBrush = d2d.GetSolidBrush();
	D2D1_RECT_F rectf = D2D1::RectF(0, 0, (float)image->GetSize().width,
		(float)image->GetSize().height);

	d2d.GetRT()->SetTransform(D2D1::Matrix3x2F::Translation(X,Y));
	d2d.GetRT()->FillRectangle(rectf, pBrush);
}
void GrafixD2::DrawSprite(
	D2D1_MATRIX_3X2_F &matTrans,
	D2D1_RECT_F &PosSize, ID2D1Bitmap *pSprite,
	D2D1_BITMAP_PROPERTIES bp, float Opacity,
	D2D1_BITMAP_INTERPOLATION_MODE InterpMode,
	D2D1_RECT_F *ClipRect)
{
	d2d.GetRT()->SetTransform(matTrans);
	d2d.GetRT()->DrawBitmap(pSprite, PosSize, Opacity, InterpMode, ClipRect);
	
	//reset transform so we have no carry-over to next sprite
	d2d.GetRT()->SetTransform(D2D1::Matrix3x2F::Identity());
}

void GrafixD2::RenderText(LPWSTR String, IDWriteTextFormat *pFormat,
	const D2D1_RECT_F &DrawRect, D2D1_COLOR_F &Color)
{
	ID2D1SolidColorBrush *pBrush = d2d.GetSolidBrush();
	pBrush->SetColor(Color);

	UINT strLen = lstrlen(String);
	d2d.GetRT()->DrawTextW(String, strLen, pFormat, DrawRect, pBrush);
}

HRESULT GrafixD2::StartFrame()
{
	HRESULT hr = d2d.CreateDeviceResources();

	if (SUCCEEDED(hr))
	{
		d2d.GetRT()->BeginDraw();		
		D2_MATRIX_IDENTITY(matID);
		d2d.GetRT()->SetTransform(matID);
		d2d.GetRT()->Clear(ColorBlack);		
	}

	return hr;
};

HRESULT GrafixD2::EndFrame()
{
	HRESULT hr = d2d.GetRT()->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		d2d.DiscardDeviceResources();
		hr = S_OK;
	}

	return hr;
};
