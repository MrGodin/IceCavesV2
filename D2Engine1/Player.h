#pragma once
#include "UtilsD2.h"
#include "Sprite.h"
#include "PlayerState.h"
class Player : public Sprite
{
public:
	Player(float2 pos, float width, float height, ID2D1Bitmap *bmp, D2D1_RECT_F cliprect);
	virtual void Update(float dt)override;
	virtual D2D_RECT_F GetDrawSize()override;
	virtual RectF GetAABB()override;
	virtual float2  GetVelocity()override;
	virtual float2  GetPosition()override;
	virtual void   SetVelocity(const float2 v)override;
	virtual void   SetPosition(const float2 p)override;
	virtual float  GetRadius()override;
	virtual float  GetMass()override;
	virtual float2  GetCenter()override;
	virtual void   Rebound(const float2 normal)override;
	virtual  PlayerCore* GetCore()override;
protected:
	PlayerCore core;
};
