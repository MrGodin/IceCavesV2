#pragma once

#include "Cores.h"
#include "rect.h"
class PlayerState
{
public:
	PlayerState(PlayerCore* core)
		:
		pCore(core)
	{}
	virtual void Update(float dt) = 0;
	virtual void OnDirectionPress() {}
	virtual void OnDirectionRelease() {}
	virtual void OnJumpPress() {}
	virtual void OnJumpRelease() {}
	virtual void OnCollision(RectF& objRect,RectF& tileRect) {};
	virtual void Transition(PlayerState* state)
	{
		pCore->state = state;
		delete this;
	}
	~PlayerState() {}
protected:
	PlayerCore* pCore;
};