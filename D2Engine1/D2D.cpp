#include "D2D.h"
D2D::D2D(HWND WinHandle)
	:
	m_hwnd(WinHandle),
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(nullptr)
{
	HRESULT hr = CreateDeviceIndependentResources();
	if (SUCCEEDED(hr))
	{
		hr = CreateDeviceResources();
	}
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Direct2D failed to initialize.", L"Initialization error.", MB_OK);
		PostQuitMessage(0);
	}

}

D2D::~D2D()
{
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
}

HRESULT D2D::CreateDeviceIndependentResources()
{
	// Create a Direct2D factory.
	return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);	
}
//=========================================================================
HRESULT D2D::CreateDeviceResources()
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
void D2D::DiscardDeviceResources()
{
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pWhiteBrush);

}
//=====================================================================
void D2D::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}

D2D1_POINT_2F D2D::GetDpi() const
{
	D2D1_POINT_2F dpi;
	m_pDirect2dFactory->GetDesktopDpi(&dpi.x, &dpi.y);
	return dpi;
}

ID2D1SolidColorBrush* D2D::GetSolidBrush()const
{
	return m_pWhiteBrush;
}