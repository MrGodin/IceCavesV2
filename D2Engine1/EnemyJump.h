#pragma once
#include "ObjectState.h"

class EnemyJump : public EnemyState
{
protected:
	bool isMoving;
	bool isThrusting;
public:
	EnemyJump(EnemyCore& core, bool moving, bool boosting, float initialYVel = 0.0f)
		:
		EnemyState(core),
		isMoving(moving),
		isThrusting(boosting)
	{
		pCore.Vel.y = initialYVel;
	}
	virtual void Update(float dt)override;
	virtual void OnCtrlDirChange(TDirection& d)override;
	virtual void OnCtrlDirRelease()override;
	virtual void OnCtrlJumpRelease()override;
	virtual void OnCtrlJumpPress()override;
	virtual void OnCollision(const RectF& rect, const RectF& FRect)override;
};