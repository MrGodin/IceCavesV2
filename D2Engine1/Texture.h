#pragma once

#include "UtilsD2.h"
#include "ImageGrid.h"


class Texture
{
public:
	Texture() {};
	Texture(ID2D1HwndRenderTarget *m_pRt);
	Texture(ID2D1HwndRenderTarget *m_pRt,const std::wstring &Basename,UINT clipsize);
	void Load(const std::wstring &Basename, UINT clipsize);
	void GetImageData(D2D1_RECT_U &PosSize, BYTE** ppPixels, UINT& stride)const;
	D2D1_RECT_F GetClip(UINT index) { return grid.GetD2ClipRect((float)index); }
	UINT Width() const;
	UINT Height() const;
	IWICBitmap *GetWicBitmap() const { return pBitmap; };
	IWICBitmap* GetClip64(D2D1_RECT_U &PosSize);
	ID2D1Bitmap* GetBmp() { return bmp; }
	~Texture();
	
private:
	ID2D1Bitmap** images = nullptr;
	IWICBitmap *pBitmap;
	UINT width, height;
	WICPixelFormatGUID pf;
	IWICBitmap* pCopyBitMap = nullptr;
	ID2D1Bitmap* bmp = nullptr;
	IWICImagingFactory *pFactory = nullptr;
	ID2D1HwndRenderTarget *m_pRT = 0;
	GridF grid;
	UINT clipSize;
};

