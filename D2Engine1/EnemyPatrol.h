#pragma once

#include "ObjectState.h"
class EnemyPatrol : public EnemyState
{
private:
	_EventTimer ETimer;
	float moveRadius;
	float startX;
public:
	EnemyPatrol(EnemyCore& core,float move_Radius)
		:
		EnemyState(core),
		moveRadius(move_Radius),
		ETimer(Math::RandFloat(0.25f, 2.0f))
	{
		startX = pCore.Pos.x;
		pCore.angle = 0.0f;
		pCore.Vel.y = 0.0f;

	}
	virtual void Update(float dt)override;

	virtual void OnUnsupported()override;
	virtual void OnCollision(const RectF& rect, const RectF& FRect)override;
	virtual void OnCtrlDirChange(TDirection& d);
};