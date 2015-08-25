#pragma once

#pragma once


#include "UtilsD2.h"
#include "rect.h"
#include <vector>
class CollidableObject
{
protected:
	std::vector<CollidableObject*>children;
	UINT type = 0;

public:
	CollidableObject() {}
	virtual RectF GetAABB() = 0;
	virtual float2  GetVelocity() = 0;
	virtual float2  GetPosition() = 0;
	virtual void   SetVelocity(const float2 v) {};
	virtual void   SetPosition(const float2 p) {};
	virtual float  GetRadius() = 0;
	virtual float  GetMass() = 0;
	virtual float2  GetCenter() = 0;
	virtual void   Rebound(const float2 normal) {};
	virtual bool   OnCollision(CollidableObject* in_obj) { return false; };
	virtual class PlayerCore* GetCore() { return NULL; };
	virtual ~CollidableObject() {};

	UINT Type() { return type; }



};