#pragma once
#include "ObjectState.h"
class EnemyMove : public EnemyState
{
private:
	_EventTimer ETimer;
public:
	EnemyMove(EnemyCore& core)
		:
		EnemyState(core),
		ETimer(Math::RandFloat(1.0f, 6.0f))
	{
		pCore.angle = 0.0f;
		pCore.Vel.y = 0.0f;
		
	}
	virtual void Update(float dt)override;
	
	virtual void OnUnsupported()override;
	virtual void OnCollision(const RectF& rect, const RectF& FRect)override;
};