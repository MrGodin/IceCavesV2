#include "IceCaves.h"


IceCaves::IceCaves()
{
	srand((UINT)time(0));
}

IceCaves::~IceCaves()
{
	SAFE_DELETE(d2d);
	SAFE_DELETE(game);
	SAFE_DELETE(pD3D);
	CoUninitialize();
}

void IceCaves::Run()
{
	// changed to isRunning because it made more sense, 
	// since Game::Run returns true is isRunning
	BOOL isRunning = TRUE;
	MSG msg{};

	dt.start();

	while (isRunning)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				isRunning = FALSE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// while will check if done is true or false, 
			// so no need to check it here also
			isRunning = game->Run(dt);
		}
	}	
}

HRESULT IceCaves::Initialize(UINT ScreenW, UINT ScreenH)
{
	// Register the window class and call methods for instantiating drawing resources

	// Use HeapSetInformation to specify that the process should
	// terminate if the heap manager detects an error in any heap used
	// by the process.
	// The return value is ignored, because we want to continue running in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	
	D2D1_POINT_2U windowSize;
	HRESULT hr = CoInitialize(NULL);

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

		// Create the window.
		m_hwnd = CreateWindow(
			L"Burgh2",
			L"Caves of Burgh",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenW,
			ScreenH,
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
			);

		hr = m_hwnd ? S_OK : E_FAIL;
	}
	
	// Initialize Direct2D.
	if (SUCCEEDED(hr))
	{
		d2d = new D2D(m_hwnd);
		hr = d2d ? S_OK : E_FAIL;

	}
	if (SUCCEEDED(hr))
	{
		// Because the CreateWindow function takes its size in pixels,
		// obtain the system DPI and use it to scale the window size.
		// The factory returns the current system DPI. This is also the value it will use
		// to create its own windows.		
		D2D1_POINT_2F dpi = d2d->GetDpi();
		windowSize.x = static_cast<UINT>(ceil((FLOAT)ScreenW * dpi.x / 96.f));
		windowSize.y = static_cast<UINT>(ceil((FLOAT)ScreenH * dpi.y / 96.f));
		SetWindowPos(m_hwnd, nullptr, 0, 0, windowSize.x, windowSize.y, SWP_SHOWWINDOW);
		
		//ShowWindow(m_hwnd, SW_SHOWNORMAL);
		//UpdateWindow(m_hwnd);
	}

	// Initialize Game
	if (SUCCEEDED(hr))
	{
		pD3D = new Direct3D10(m_hwnd, windowSize.x, windowSize.y);
		hr = pD3D ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		UINT w = windowSize.x;// -(2 * (64 * 3));
		UINT h = windowSize.y;// -(2 * (64 * 3));

		game = new Game(*d2d, *pD3D,w,h);
		hr = game ? S_OK : E_FAIL;
	}
	
	return hr;
}

LRESULT IceCaves::MsgProc(HWND WinHandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	controler.MsgProc(WinHandle, Message, wParam, lParam);
	switch (Message)
	{
	case WM_SIZE:
		d2d->OnResize(LOWORD(lParam), HIWORD(lParam));
		if (game)
			game->Resize(LOWORD(lParam), HIWORD(lParam));
		result = 0;
		break;
	case WM_DISPLAYCHANGE:
		InvalidateRect(WinHandle, NULL, FALSE);
		result = 0;
		break;
	case WM_PAINT:
		ValidateRect(WinHandle, NULL);
		result = 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		result = 1;
		break;
	default:
		result = DefWindowProc(WinHandle, Message, wParam, lParam);
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	IceCaves *pApp = nullptr;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		pApp = (IceCaves *)pcs->lpCreateParams;

		SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			(LONG_PTR)pApp  // Needed to be LONG_PTR instead of ULONG_PTR
			);

		result = 1;
	}
	else
	{	
		pApp = reinterpret_cast<IceCaves *>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

		if (pApp)
		{
			result = pApp->MsgProc(hwnd, message, wParam, lParam);
		}
		else
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}
//====================================
