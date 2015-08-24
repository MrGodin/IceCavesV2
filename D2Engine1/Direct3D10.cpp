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
		nullptr, flags, D3D10_FEATURE_LEVEL_10_1, D3D10_SDK_VERSION, &sd,
		&psc, &pDevice);


	pDevice->QueryInterface(&pDxgiDevice);
	pDxgiDevice->GetAdapter(&pAdapter);
	pAdapter->GetParent(IID_PPV_ARGS(&pDxgiFactory));

}


Direct3D10::~Direct3D10()
{
	SAFE_RELEASE(psc);
	SAFE_RELEASE(pDevice);
	SAFE_RELEASE(pDxgiDevice);
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pDxgiFactory);
}


IDXGISwapChain *Direct3D10::GetSwapChain()const
{
	return psc;
}