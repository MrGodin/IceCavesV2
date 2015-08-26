#pragma once
#include "Game.h"
#include "D2D.h"


//============================================================
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
	);

//=============================================================
class IceCaves
{
public:
	IceCaves();
	~IceCaves();

	HRESULT Initialize(UINT ScreenW, UINT ScreenH);
	LRESULT MsgProc(HWND WinHandle, UINT Message, WPARAM wParam, LPARAM lParam);
	void Run();

	HWND m_hwnd;
	D2D *d2d;
	Game *game;
	_DeltaTime dt;

};
