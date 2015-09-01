#pragma once
#include "Sprite.h"

enum enemyType{etLevel1Roamer,
	etLevel1GuardTank,
	etLeve1Cannon,
	etAmmo,

	etNumbTypes};
class Enemy : public Sprite
{
public:
	struct EnemyDesc
	{
		EnemyCore core;
		Sprite::SpriteDesc sprite;
	};
protected:
	EnemyDesc mainDesc;
public:
	Enemy(EnemyDesc& desc);
	virtual ~Enemy();
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
	virtual TDirection GetDirection() { return core.dir; }
	virtual ObjectState* GetState();

	virtual float GetHitPts() { return core.hit_points; }
	virtual void SetHitPts(const float& val) { core.hit_points = val; }
	virtual void SetHitPtsInc(const float& val) { core.hit_points += val; }
	
protected:
	EnemyCore core;
};