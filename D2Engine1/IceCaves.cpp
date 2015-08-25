
#include "IceCaves.h"

IceCaves::IceCaves(GrafixD2& gfx)
	:
	Game(gfx),
	textures(gfx.GetRT()),
	viewport(gfx, { 0,0,(int)gfx.WindowSize().x,(int)gfx.WindowSize().y }),
	camera(viewport, (float)viewport.GetWidth(), (float)viewport.GetHeight())
{
	running = TRUE;
	initStaticVars();
	GameLevelData d;
	sprintf_s(d.mapStr, "%s", pLevel2String);
	d.map_height = iLevel2Height;
	d.map_width = iLevel2Width;
	d.map_tileHeight = d.map_tileWidth = 64;
	float2 sp(0.0f, 0.0f);

	
	
	OnResetDevice();
	loadMap(d, sp);

}
HRESULT IceCaves::OnRender()
{
	HRESULT hr = S_OK;
	
	pMap->GetDrawable().Rasterize(gfx);
	return hr;
};

BOOL IceCaves::OnUpdate(float dt)
{
	//update game running time
	camera.UpdatePosition(float2(600.0f, 0.0f));
	m_runTime += dt;
	return TRUE;
};
// Release created device objects
void IceCaves::ShutDown()
{
	SAFE_DELETE(pMap);
}
void IceCaves::OnLostDevice()
{
	textures.OnLostDevice();
}
void IceCaves::OnResetDevice()
{
	loadImages();
}
void IceCaves::initStaticVars()
{
	MapTile::SetWidthHeight(64, 64);
}
void IceCaves::loadImages()
{
	textures.AddTexture(L"media\\levelsprite2.png",64);
}
//=====================================================
void IceCaves::loadMap(GameLevelData& data, float2 startPt)
{
	SAFE_DELETE(pMap);
	ID2D1Bitmap* b = textures.GetTexture(0);
	pMap = new TileMap(camera, b, data);
	pMap->CreateImageGrid(512, 512, 64);
	pMap->Create(startPt);
}
///////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		GrafixD2 *pDemoApp = (GrafixD2 *)pcs->lpCreateParams;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			PtrToUlong(pDemoApp)
			);

		result = 1;
	}
	else
	{
		GrafixD2 *pDemoApp = reinterpret_cast<GrafixD2 *>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA
				)));

		bool wasHandled = false;

		if (pDemoApp)
		{
			//return pDemoApp->AppWndProc(hwnd, message, wParam, lParam);
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pDemoApp->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_PAINT:
			{
				//pDemoApp->OnRender();
				ValidateRect(hwnd, NULL);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			result = 1;
			wasHandled = true;
			break;
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}
//====================================
