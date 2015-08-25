#pragma once
#include "CollidableObject.h"
#include "Collisions.h"
class Collide
{
public:
	Collide() {}
	virtual void SphericalCollision(CollidableObject& obj) = 0;
	virtual void MapCollision() = 0;


};