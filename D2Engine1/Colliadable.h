#pragma once
#include "CollidableObject.h"
#include "Collisions.h"
class Collide
{
public:
	Collide() {}
	virtual bool SphericalCollision(CollidableObject& obj) = 0;
	virtual void MapCollision() = 0;


};