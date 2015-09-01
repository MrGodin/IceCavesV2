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
	CollidableObject()
	
	{}
	virtual RectF GetAABB() { return RectF(0, 0, 0, 0); };
	virtual float2  GetVelocity() { return float2(0, 0); }
	virtual float2  GetPosition() { return float2(0, 0); }
	virtual void   SetVelocity(const float2 v) {};
	virtual void   SetPosition(const float2 p) {};
	virtual float  GetRadius() {
		return 0.0f;
	};
	virtual TDirection GetDirection() { TDirection d; d.SetInvalid(); return d; }
	virtual TDirection GetOppositeDirection() { TDirection d; d.SetInvalid(); return d; }
	virtual float  GetMass() { return 0.0f; };
	virtual float2  GetCenter() { return float2(0, 0); }
	virtual void   Rebound(const float2 normal) {};
	virtual bool Active() { return true; }
	virtual class ObjectState* GetState() {	return 0; };
	

	virtual ~CollidableObject() {};

	UINT Type() { return type; }



};