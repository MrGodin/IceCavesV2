#pragma once

#include "D2D.h"
#include "GrafixD2.h"
#include "Texture.h"
#include "Camera.h"
#include "viewport.h"
#include "MapTile.h"
#include "TileMap.h"
#include "UtilsD2.h"
#include "Player.h"
#include "PlayerControl.h"

extern PlayerControl controler;

class Game
{
	// classes are private by default
	GrafixD2 gfx;
	D2D &d2d;
	Texture mapSprite;
	float m_runTime = 0.0f;
	ID2D1Bitmap *pMapBitmap = nullptr;
	
	Camera camera;
	Viewport viewport;
	TileMap* pMap = NULL;
	BOOL running = FALSE;
	Player* pPlayer = nullptr;
	
public:
	Game(D2D &d2d, UINT Width, UINT Height);
	~Game();
	void OnLostDevice();
	void OnResetDevice();
	void loadImages();
	void initStaticVars();
	void loadMap(GameLevelData& data, float2 startPt);
	void CreatePlayer();
	void Resize(float w, float h) { camera.Resize(w, h); }
	BOOL OnUpdate(float dt);
	HRESULT OnRender();
	BOOL Run(_DeltaTime &DeltaTime);

};
