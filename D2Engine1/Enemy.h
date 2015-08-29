#pragma once
#include "Sprite.h"


class Enemy : public Sprite
{
public:
	Enemy(float2 pos, float width, float height, ID2D1Bitmap *bmp, D2D1_RECT_F cliprect);
	~Enemy();
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
	virtual ObjectState* GetState();
private:
	EnemyCore core;
};