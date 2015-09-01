#pragma once

#include "ObjectState.h"

class EnemyAmmoMove : public EnemyState
{
protected:
	
public:
	EnemyAmmoMove(EnemyCore& core,  float initialYVel = 0.0f)
		:
		EnemyState(core)
		
	{
		
	}
	virtual void Update(float dt)override;
	virtual void OnCtrlDirChange(TDirection& d)override;
	virtual void OnCtrlDirRelease()override;
	virtual void OnCtrlJumpRelease()override;
	virtual void OnCtrlJumpPress()override;
	virtual void OnCollision(const RectF& rect, const RectF& FRect)override;
};