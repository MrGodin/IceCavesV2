#include "Game.h"
#include "IceCaves.h"
#include "Desc.h"

Game::Game(D2D &d2d, Direct3D10& d3d ,UINT Width, UINT Height)
	:
	d2d(d2d),
	d3d(d3d),
	gfx(d2d),
	viewport(gfx, { 0,0,(float)Width,(float)Height}),
	camera(viewport, (float)Width, (float)Height),
	StaticAnimate(camera),
	Enemies(camera,StaticAnimate)
	
{
	viewPortPos = float2(0.0f,0.0f);
	Drawable::SetViewPort(viewPortPos);
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
	StaticAnimate.SetImage(pMapBitmap);
	running = TRUE;
}

HRESULT Game::OnRender()
{
	pMap->GetDrawable().Rasterize(gfx);
	camera.Rasterize(pPlayer->GetDrawable());
	Enemies.Rasterize();
	StaticAnimate.Rasterize();
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
	StaticAnimate.Update(dt);
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

	pMap = new TileMap(camera,Enemies, pMapBitmap, data);
	pMap->CreateImageGrid(512, 512, 64);
	pMap->Create(startPt);
}
//==========================
void Game::CreatePlayer()
{
	Player::PlayerDesc desc;
	PlayerCore core;
	StaticAnimation::AnimationDesc an;
	Sprite::SpriteDesc sprite;

	float x = 800 / 2;
	float y = 600 / 2;
	
	D2D1_RECT_F g = Math::GetImageRectFromIndex(33, pMapBitmap, 64, 64);

	sprite.width = 42;
	sprite.height = 42;

	core.mass = 1.75;
	

	an.bmp = pMapBitmap;
	an.clipHeight = 64;
	an.clipWidth = 64;
	an.drawHeight = 42;
	an.drawWidth = 42;// sprite.width;
	an.keep_alive = true;
	an.frames = 2;
	an.startFrame = 0;
	an.endFrame = an.frames - 1;
	an.life_span = 0.5f;
	an.clipOffsetW = an.clipOffsetH = 0;
	an.do_animate = false;
	an.index = 0;
	an.clip_startpos = float2(g.left, g.top);
	an.pos = float2(x,y);
	core.Pos = an.pos;
	desc.core = core;
	sprite.animateDesc = an;
	desc.sprite = sprite;
	pPlayer = new Player(desc);
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
	
}
//////////////////////////////////////////////////////////////////////////////
BOOL Game::Run(_DeltaTime &DeltaTime)
{	
#ifdef _DEBUG
	float deltaTime = 1.0f / 60.0f;
#else
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