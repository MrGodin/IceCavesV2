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
#include "DirectWrite.h"
#include "Enemy.h"
#include "EnemyContainer.h"
#include "StaticAnimationContainer.h"
#include "Direct3D10.h"

extern PlayerControl controler;

class Game
{
	// classes are private by default
	GrafixD2 gfx;
	D2D &d2d;
	Direct3D10& d3d;
	Texture mapSprite;
	float m_runTime = 0.0f;
	ID2D1Bitmap *pMapBitmap = nullptr;
	
	Camera camera;
	Viewport viewport;
	float2 viewPortPos;
	TileMap* pMap = NULL;
	BOOL running = FALSE;
	Player* pPlayer = nullptr;
	
	EnemyContainer Enemies;
	StaticAnimationContainer StaticAnimate;
public:

	Game(D2D &d2d, Direct3D10& d3d, UINT Width, UINT Height);
	~Game();
	void OnLostDevice();
	void OnResetDevice();
	void loadImages();
	void initStaticVars();
	void loadMap(GameLevelData& data, float2 startPt);
	void CreatePlayer();
	void Resize(float w, float h) 
	{
		float newW = w - viewPortPos.x;
		float newH = h - viewPortPos.y;
		camera.Resize(newW,newH);
	}
	void renderText();
	void createEnemies();
	BOOL OnUpdate(float dt);
	HRESULT OnRender();
	BOOL Run(_DeltaTime &DeltaTime);

};
