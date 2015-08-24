
#pragma once
#include "UtilsD2.h"

class SpriteSheetImage
{
public:
	SpriteSheetImage();
	~SpriteSheetImage();
	void ReleaseCreatedImageData();
	void CreateImage(LPCWSTR in_textureFilename);
	void draw();
	void setXY(float x, float y);
	D2Bitmap GetBitmap(){ return m_pBitmap; }
	D2BitmapBrush GetBitmapBrush(){ return m_pBitmapBrush; }
private:
	float m_x, m_y;
	ID2D1BitmapBrush *m_pBitmapBrush = 0;
	D2Bitmap m_pBitmap= 0;
	LPCWSTR m_textureFilename;
	//==============================
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	IWICImagingFactory* pIWICFactory = NULL;
};