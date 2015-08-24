
#include "SpriteSheetImage.h"

SpriteSheetImage::SpriteSheetImage()
{}
void SpriteSheetImage::CreateImage(LPCWSTR in_textureFilename)
{
	m_x = m_y = 0;
	m_textureFilename = in_textureFilename;
	
	
	if(FAILED( CoCreateInstance(
		CLSID_WICImagingFactory,
		//CLSID_WICImagingFactory1,
		//CLSID_WICImagingFactory2,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&pIWICFactory
		)))
	{
		int x = 0;
	}
		

	HRESULT hr;
	hr = pIWICFactory->CreateDecoderFromFilename(
		m_textureFilename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);

	if (!SUCCEEDED(hr))
	{
		int x = 0;
	}

	hr = pDecoder->GetFrame(0, &pSource);

	if (!SUCCEEDED(hr))
	{
		int x = 0;
	}

	hr = pIWICFactory->CreateFormatConverter(&pConverter);

	if (!SUCCEEDED(hr))
	{
		int x = 0;
	}

	hr = pConverter->Initialize(
		pSource,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeMedianCut
		);

	if (!SUCCEEDED(hr))
	{
		int x = 0;
	}

	/*hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		&m_pBitmap
		);*/

	if (!SUCCEEDED(hr))
	{
		int x = 0;
	}
	

	/*hr = m_pRenderTarget->CreateBitmapBrush(
		m_pBitmap,
		&m_pBitmapBrush
		);
*/
	if (!SUCCEEDED(hr))
	{
		int x = 0;
	}
	
	ReleaseCreatedImageData();
}

void SpriteSheetImage::ReleaseCreatedImageData()
{
	
	SAFE_RELEASE(pIWICFactory);
	SAFE_RELEASE(pConverter);
	SAFE_RELEASE(pDecoder);
	SAFE_RELEASE(pStream);
	SAFE_RELEASE(pSource);
}
SpriteSheetImage::~SpriteSheetImage()
{
	ReleaseCreatedImageData();
	SAFE_RELEASE(m_pBitmap);
	SAFE_RELEASE(m_pBitmapBrush);
}

void SpriteSheetImage::draw() {
	//m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(m_x, m_y));
	//m_pRenderTarget->FillRectangle(D2D1::RectF(0, 0, (float)m_pBitmap->GetSize().width, (float)m_pBitmap->GetSize().height), m_pBitmapBrush);
}

void SpriteSheetImage::setXY(float x, float y)
{
	m_x = x;
	m_y = y;
}