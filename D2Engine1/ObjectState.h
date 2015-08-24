#pragma once

#include "Cores.h"
class ObjectState
{
public:
	ObjectState(ObjectCore* core)
		:
		pCore(core)
	{}
	virtual void OnDirectionPress() {}
	virtual void OnDirectionRelease() {}
	virtual void OnJumpPress() {}
	virtual void OnJumpRelease() {}
	virtual void OnCollision(RectF& objRect,RectF& tileRect) {};
	~ObjectState() {}
protected:
	ObjectCore* pCore;
};