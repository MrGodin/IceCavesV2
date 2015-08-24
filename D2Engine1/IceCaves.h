#pragma once
#include "Game.h"
#include "GrafixD2.h"
#include "Images.h"
#include "Camera.h"
#include "viewport.h"
#include "MapTile.h"
#include "TileMap.h"

//============================================================
extern LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
	);

//=============================================================
class IceCaves : public Game
{
private:
	float m_runTime = 0.0f;
	Images textures;
	Camera camera;
	Viewport viewport;
	TileMap* pMap = NULL;
public:
	IceCaves(GrafixD2& gfx);
	~IceCaves(){}
	virtual BOOL OnUpdate(float dt)override;
	virtual HRESULT OnRender()override;
	virtual void ShutDown()override;
	virtual void OnLostDevice()override;
	virtual void OnResetDevice()override;
	void loadImages();
	void initStaticVars();
	void loadMap(GameLevelData& data,float2 startPt);
	
};
