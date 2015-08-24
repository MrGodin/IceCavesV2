#pragma once


#include "windows.h"
struct Vec2F
{
public:
	float x, y;
	Vec2F(float x1, float y1)
		:
		x(x1),
		y(y1)
	{}
};
class D2Mouse
{
private:
	bool RightButton = false;
	bool LeftButton = false;
	POINT pt;
	Vec2F mouse;
	void OnButtonRelease(UINT btn)
	{
		switch (btn)
		{
		case WM_RBUTTONUP:
			RightButton = false;
			break;

		case WM_LBUTTONUP:
			LeftButton = false;
			break;
		}

	}
	void OnButtonPress(UINT btn)
	{
		switch (btn)
		{
		case WM_RBUTTONDOWN:
			RightButton = true;
			break;

		case WM_LBUTTONDOWN:
			LeftButton = true;
			break;
		}



	}
public:
	D2Mouse() {}
	LRESULT D2MouseWndMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_MOUSEMOVE:
		{
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);
			mouse = Vec2F((float)pt.x, (float));

		}
		break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
			OnButtonPress(msg);
			break;
		case WM_RBUTTONUP:
		case WM_LBUTTONUP:
			OnButtonRelease(msg);
			break;
		}
		return 0;
	}
	bool isLeft() { return LeftButton; }
	bool isRight() { return RightButton; }
	Vec2F& getMouse() { return mouse; }
};