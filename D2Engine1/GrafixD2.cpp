

#include "GrafixD2.h"

GrafixD2::GrafixD2() :
m_hwnd(NULL),
m_pDirect2dFactory(NULL)
{
}
//=====================================================
GrafixD2::~GrafixD2()
{
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	

}
//==============================================================

//=====================================================================
HRESULT GrafixD2::Initialize()
{
	if (initialized)// already initialized
		return 0;

	srand((UINT)time(0));
	HRESULT hr;
	
	// Initialize device-indpendent resources, such
	// as the Direct2D factory.
	hr = CreateDeviceIndependentResources();
	

	if (SUCCEEDED(hr))
	{
		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"Burgh2";

		RegisterClassEx(&wcex);


		// Because the CreateWindow function takes its size in pixels,
		// obtain the system DPI and use it to scale the window size.
		FLOAT dpiX, dpiY;

		// The factory returns the current system DPI. This is also the value it will use
		// to create its own windows.
		m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);


		// Create the window.
		windowSize.x = 800;// static_cast<UINT>(ceil(640.f * dpiX / 96.f));
		windowSize.y = 600;// static_cast<UINT>(ceil(480.f * dpiY / 96.f));
		m_hwnd = CreateWindow(
			L"Burgh2",
			L"Caves of Burgh",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
			static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
			);
		hr = m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
	}
	if (SUCCEEDED(hr))
	{
		hr = CreateDeviceResources();
	}
	initialized = true;
	
	return hr;
}
//==============================================================================
void GrafixD2::Rasterize(Drawable& obj)
{
	 obj.Rasterize(*this);
}

//=============================================================================
void GrafixD2::DrawLine(Point2F start, Point2F end, D2Brush brush, float lineWidth)
{
	m_pWhiteBrush->SetColor({ 0.0f,0.0f,1.0f,1.0f });
	m_pRenderTarget->DrawLine(
		D2D1::Point2F(start.x, start.y),
		D2D1::Point2F(end.x, end.y),
		m_pWhiteBrush,
		lineWidth
		);
};
//==============================================================================
void GrafixD2::DrawRectangle(D2D1_RECT_F rect, D2Brush brush)
{
	m_pRenderTarget->FillRectangle(&rect, brush);
}
void GrafixD2::DrawBitmap(D2Bitmap image, D2Brush brush,RECT rect, float X, float Y)
{
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(X,Y));
	m_pRenderTarget->FillRectangle(D2D1::RectF(0, 0, (float)image->GetSize().width, (float)image->GetSize().height), m_pWhiteBrush);//brush);
}
void GrafixD2::DrawSprite(D2D1_RECT_F &PosSize, ID2D1Bitmap *pSprite,
	D2D1_BITMAP_PROPERTIES bp, float Opacity,
	D2D1_BITMAP_INTERPOLATION_MODE InterpMode,
	D2D1_RECT_F *ClipRect)
{
	m_pRenderTarget->DrawBitmap(pSprite, PosSize, Opacity, InterpMode, ClipRect);
}

void GrafixD2::RenderText(LPWSTR String, IDWriteTextFormat *pFormat,
	const D2D1_RECT_F &DrawRect, D2D1_COLOR_F &Color)
{
	m_pWhiteBrush->SetColor(Color);
	UINT strLen = lstrlen(String);
	m_pRenderTarget->DrawTextW(String, strLen, pFormat, DrawRect, m_pWhiteBrush);
}

HRESULT GrafixD2::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	return hr;
}
//=========================================================================
HRESULT GrafixD2::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
			);

		// Create a Direct2D render target.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
			);


		if (SUCCEEDED(hr))
		{
			// Create a gray brush.
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::White),
				&m_pWhiteBrush
				);
		}
		
	}

	return hr;
}
//=====================================================================
void GrafixD2::DiscardDeviceResources()
{
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pWhiteBrush);
	
}
//=====================================================================
HRESULT GrafixD2::StartFrame()
{
	HRESULT hr = S_OK;

	hr = CreateDeviceResources();
	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->BeginDraw();
		
		D2_MATRIX_IDENTITY(matID);
		m_pRenderTarget->SetTransform(matID);

		m_pRenderTarget->Clear(ColorBlack);
		
	}
	return hr;
};
HRESULT GrafixD2::EndFrame()
{
	HRESULT hr;
	hr = m_pRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
	return hr;
};

//===================================================================
void GrafixD2::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}
//=====================================================================
///////////////////////////////////////////////////////////////////////////////

