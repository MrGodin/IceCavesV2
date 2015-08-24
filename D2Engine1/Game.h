#pragma once

#include "UtilsD2.h"


class Game
{
protected:
	BOOL running = FALSE;
	class GrafixD2& gfx;
public:
	
	Game(GrafixD2& in_gfx)
	:
	gfx(in_gfx)
	{};
	virtual ~Game() {}
	_DeltaTime dt;
	virtual BOOL OnUpdate(float dt) = 0;
	virtual HRESULT OnRender() = 0;
	virtual void ShutDown() = 0;
	virtual void OnLostDevice() = 0;
	virtual void OnResetDevice() = 0;
	
	BOOL Run();
	
};