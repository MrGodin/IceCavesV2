

#pragma once
#include "ObjectState.h"

class PlayerJump : public PlayerState
{
protected:
	bool isMoving;
	bool isThrusting;
	float thrust;
public:
	PlayerJump(PlayerCore& core,bool moving,bool boosting,float initialYVel = 0.0f)
		:
		PlayerState(core),
		isMoving(moving),
		isThrusting(boosting)
	{
		if(isThrusting)
		  pCore.Vel.y = 0.0f;

		thrust = -20.0f;
	}
	virtual void Update(float dt)override;
	virtual void OnCtrlDirChange(TDirection& d)override;
	virtual void OnCtrlDirRelease()override;
	virtual void OnCtrlJumpRelease()override;
	virtual void OnCtrlJumpPress()override;
	virtual void OnCollision(const RectF& rect, const RectF& FRect)override;
};