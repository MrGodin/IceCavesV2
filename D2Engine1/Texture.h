#pragma once

#include "UtilsD2.h"
#include "ImageGrid.h"


class Texture
{
public:
	Texture();
	Texture(const std::wstring &Basename);
	void Load(const std::wstring &Basename);
	void GetImageData(D2D1_RECT_U &PosSize, BYTE** ppPixels, UINT& stride)const;
	UINT Width() const;
	UINT Height() const;
	IWICBitmap *GetWicBitmap() const { return pBitmap; };
	IWICBitmap* GetClip64(D2D1_RECT_U &PosSize);
	~Texture();
	
private:
	IWICImagingFactory *pFactory = nullptr;
	IWICBitmap *pBitmap;
	UINT width, height;
	WICPixelFormatGUID pf;
};

