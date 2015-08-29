#include "Game.h"
#include "IceCaves.h"

Game::Game(D2D &d2d, UINT Width, UINT Height)
	:
	d2d(d2d),
	gfx(d2d),
	viewport(gfx, { 0,0,(float)Width,(float)Height}),
	camera(viewport, (float)Width, (float)Height),
	Enemies(camera)
{
	
	srand((unsigned int)time(0));
	OnResetDevice();
	float w = Width;
	float h = Height;
	initStaticVars();
	camera.Resize(w, h);
	GameLevelData d;
	
	sprintf_s(d.mapStr, "%s", pLevel2String);
	d.map_height = iLevel2Height;
	d.map_width = iLevel2Width;
	d.map_tileHeight = d.map_tileWidth = 64;
	float2 sp(0.0f, 0.0f);
	loadMap(d, sp);
	CreatePlayer();
	createEnemies();
	
	running = TRUE;
}

HRESULT Game::OnRender()
{
	pMap->GetDrawable().Rasterize(gfx);
	camera.Rasterize(pPlayer->GetDrawable());
	Enemies.Rasterize();
	renderText();
	return S_OK;
};

BOOL Game::OnUpdate(float dt)
{
//update game running time
	m_runTime += dt;
//~
	controler.Poll(pPlayer);
	pPlayer->Update(dt);
	pPlayer->GetCollision().MapCollision();
	camera.UpdatePosition(pPlayer->GetPosition());
	Enemies.Update(*pPlayer, dt);
	
	return TRUE;
};

void Game::OnLostDevice()
{
	
}

void Game::OnResetDevice()
{
	loadImages();
}

void Game::loadImages()
{
	Texture t(std::wstring(L"media\\levelsprite2.png"));
	d2d.GetRT()->CreateBitmapFromWicBitmap(
		t.GetWicBitmap(), &pMapBitmap);
	
}

void Game::initStaticVars()
{
	MapTile::SetWidthHeight(64, 64);
}

//=====================================================
void Game::loadMap(GameLevelData& data, float2 startPt)
{
	SAFE_DELETE(pMap);
	RectF r(0, 0, data.map_width, data.map_height);
	camera.ConfineToMap(r);

	pMap = new TileMap(camera, pMapBitmap, data);
	pMap->CreateImageGrid(512, 512, 64);
	pMap->Create(startPt);
}
//==========================
void Game::CreatePlayer()
{
	float x =  800 / 2;
	float y =  600 / 2;
	int index = 23;
	D2D1_RECT_F g = Math::GetImageRectFromIndex(23, pMapBitmap, 64, 64);
	g.left += 16;
	g.top += 16;
	g.right -= 16;
	g.bottom -= 16;
	int row = index / 8;
	int col = index % 8; // remainder
	float dx = col * 64;
	float dy = row * 64;
	pPlayer = new Player(float2(x, y), 32, 32, pMapBitmap, g);
}
void Game::renderText()
{
	DirectWrite dw;
	D2D1_RECT_F pos = D2D1::RectF(10,10,130,26);
	D2D1_COLOR_F c = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);
	IDWriteTextFormat* fmt = dw.CreateFormat(L"Tahoma", 16.0f);
	gfx.RenderText(L"Hello", fmt, pos, c);
}
void Game::createEnemies()
{
	for (int d = 0; d < 8; d++)
	{
		float x = Math::RandFloat(600.0f,4000.0f);
		float y = 600 / 2;
		int index = 23;
		D2D1_RECT_F g = Math::GetImageRectFromIndex(27, pMapBitmap, 64, 64);
		g.left += 16;
		g.top += 16;
		g.right -= 16;
		g.bottom -= 16;
		Enemy* E;
		E = new Enemy(float2(x, y), 32, 32, pMapBitmap, g);
		Enemies.Add(E);
	}
}
//////////////////////////////////////////////////////////////////////////////
BOOL Game::Run(_DeltaTime &DeltaTime)
{	
#ifdef _DEBUG
	float deltaTime = 1.0f / 60.0f;
#elif
	float deltaTime = DeltaTime.deltaTime();
#endif

	if (OnUpdate(deltaTime) == FALSE)
		return FALSE;
	if (FAILED(gfx.StartFrame()))
		return FALSE;
	if (FAILED(OnRender()))
		return FALSE;
	if (FAILED(gfx.EndFrame()))
		return FALSE;

	return running;
}

Game::~Game()
{
	SAFE_DELETE(pMap);
	SAFE_DELETE(pPlayer);
	
}