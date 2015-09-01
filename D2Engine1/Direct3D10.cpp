#include "Direct3D10.h"
#include "UtilsD2.h"

Direct3D10::Direct3D10(HWND WinHandle, UINT WindowWidth, UINT WindowHeight)
	:
	pDevice(nullptr),
	pDxgiDevice(nullptr),
	pDxgiFactory(nullptr),
	psc(nullptr)
{
	HRESULT hr = S_OK;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
	sd.BufferDesc.Width = WindowWidth;
	sd.BufferDesc.Height = WindowHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = WinHandle;
	sd.Windowed = TRUE;

	// First flag is for interoperability with Direct2D, second flag so it runs
	// faster if not using multithreading
	UINT flags =
		D3D10_CREATE_DEVICE_BGRA_SUPPORT | D3D10_CREATE_DEVICE_SINGLETHREADED;

	hr = D3D10CreateDeviceAndSwapChain1(pAdapter, D3D10_DRIVER_TYPE_HARDWARE,
		nullptr, flags, D3D10_FEATURE_LEVEL_10_1, D3D10_1_SDK_VERSION, &sd,
		&psc, &pDevice);
	if (FAILED(hr))
	{
		int x = 0;
	}
	viewport.Width = WindowWidth / 2;
	viewport.Height = WindowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	pDevice->RSSetViewports(1, &viewport);
	ID3D10Texture2D* backBufferPtr;
	hr = psc->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&backBufferPtr);
	
	// Create the render target view with the back buffer pointer.
	 pDevice->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
	

	// Release pointer to the back buffer as we no longer need it.
	backBufferPtr->Release();
	pDevice->QueryInterface(&pDxgiDevice);
	pDxgiDevice->GetAdapter(&pAdapter);
	pAdapter->GetParent(IID_PPV_ARGS(&pDxgiFactory));

}

HRESULT Direct3D10::BeginScene()
{
	float color[4];
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	pDevice->ClearRenderTargetView(m_renderTargetView, color);
	return S_OK;
}
HRESULT Direct3D10::EndScene()
{
	psc->Present(1, 0);
	return S_OK;
}

Direct3D10::~Direct3D10()
{
	SAFE_RELEASE(psc);
	SAFE_RELEASE(pDevice);
	SAFE_RELEASE(pDxgiDevice);
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pDxgiFactory);
	SAFE_RELEASE(m_renderTargetView);
}


IDXGISwapChain *Direct3D10::GetSwapChain()const
{
	return psc;
}