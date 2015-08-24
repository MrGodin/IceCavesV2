
#include "Game.h"
#include "GrafixD2.h"
BOOL Game::Run()
{
	float deltaTime = dt.deltaTime();
#ifdef M_DEBUG
	deltaTime = 1.0f / 60.0f;
#endif


	
	if( OnUpdate(deltaTime) == FALSE)
		return FALSE;
	if (FAILED(gfx.StartFrame()))
		return FALSE;
	if (FAILED(OnRender()))
		return FALSE;
	if (FAILED(gfx.EndFrame()))
		return FALSE;

	
	return running;
}