#include "Texture.h"
#include "UtilsD2.h"



Texture::Texture()
{

}

Texture::Texture(const std::wstring &Basename)
{
	Load(Basename);
}

void Texture::Load(const std::wstring &Basename)
{
	IWICBitmapDecoder *pDecoder = nullptr;
	IWICBitmapFrameDecode *pFrame = nullptr;
	IWICFormatConverter *pConverter = nullptr;
	
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pFactory));

	if (SUCCEEDED(hr))
	{
		hr = pFactory->CreateDecoderFromFilename(Basename.c_str(), nullptr, GENERIC_READ,
			WICDecodeMetadataCacheOnDemand, &pDecoder);
	}
	if (SUCCEEDED(hr))
	{
		pDecoder->GetFrame(0, &pFrame);
	}
	if (SUCCEEDED(hr))
	{

		hr = pFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPRGBA,
			WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeCustom);
	}
	if (SUCCEEDED(hr))
	{
		hr = pFactory->CreateBitmapFromSource(pConverter, WICBitmapCacheOnDemand, &pBitmap);
        if(pBitmap)
			pBitmap->GetSize(&width, &height);	
	}
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"There was a problem loading the textures.",
			L"Error loading Textures.", MB_OK);
		PostQuitMessage(0);
	}

	// Might have to hold on to pFactory while you have a IWICBitmap active, 
	// can't remember
	

	SAFE_RELEASE(pDecoder);
	SAFE_RELEASE(pFrame);
}

IWICBitmap* Texture::GetClip64(D2D1_RECT_U &PosSize)
{
	UINT bufSize = (64) * (64)*sizeof(int);
	BYTE* pBytes =  new BYTE[bufSize];
	
	UINT stride = 0;
	
	WICRect r;
	r.X = 0;
	r.Y = 0;
	r.Height = r.Width = 64;
	D2D1_RECT_U cutout = D2D1::RectU(0, 0, 64, 64);
	GetImageData(PosSize, &pBytes, stride);
	
	
	int x = 0;

	SAFE_DELETE_ARRAY(pBytes);
	return NULL;
}
// create before passing new ppPixels*[bufSixe];
//UINT bufSize = (PosSize.right - PosSize.left) *
//(PosSize.bottom - PosSize.top) * sizeof(int);
void Texture::GetImageData(D2D1_RECT_U &PosSize, BYTE** ppPixels,UINT& stride)const
{
	// unsigned int doesn't go below 0, but if you cast to int,
	// it should make the correct comparison.
	assert((int)PosSize.left >= 0 && (int)PosSize.top >= 0);
	assert(PosSize.right <= width && PosSize.bottom <= height);
	IWICBitmapLock *pLock = nullptr;
	WICInProcPointer pPixels = nullptr;
	HRESULT hr = S_OK;

	WICRect wr;
	wr.X = PosSize.left;
	wr.Y = PosSize.top;
	wr.Width = PosSize.right;
	wr.Height = PosSize.bottom;

	hr = pBitmap->Lock(&wr, WICBitmapLockRead, &pLock);
	hr = pLock->GetStride(&stride);
	if (SUCCEEDED(hr))
	{
		UINT bufSize = (PosSize.right - PosSize.left) *
			(PosSize.bottom - PosSize.top) * sizeof(int);

		hr = pLock->GetDataPointer(&bufSize, &pPixels);
	}
	UINT ppWidth = PosSize.right - PosSize.left;
	if (SUCCEEDED(hr))
	{
		for (UINT y = PosSize.top,yy = 0; y < PosSize.bottom; ++y,yy++)
		{
			// Precalculating the offset here reduces the number of 
			// calculations the cpu has to do, by (width * (height - 1)) 
			int rowOffset = y * width;
			int texRowOffset = yy * ppWidth;

			for (UINT x = PosSize.left,xx = 0; x < PosSize.right; ++x,xx++)
			{
				int index = x + rowOffset;
				int count = texRowOffset + xx;
				(*ppPixels)[count] = *pPixels;
				pPixels++;
			}
		}

		SAFE_RELEASE(pLock);
	}

}

UINT Texture::Width() const
{
	return width;
}

UINT Texture::Height() const
{
	return height;
}

Texture::~Texture()
{
	SAFE_RELEASE(pBitmap);
	SAFE_RELEASE(pFactory);
	
}
