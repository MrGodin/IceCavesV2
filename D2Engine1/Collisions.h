#pragma once
#include "CollidableObject.h"
class Collision
{
private:
	bool static HandleSingleMapTileCollision(CollidableObject& objA,RectF& tileRect);
public:
	bool static HandleSphericalObjectCollision(CollidableObject& objA, CollidableObject& objB);
	void static HandleMapCollision(CollidableObject& objA);
	void static DoSupport(CollidableObject& objA);
	void static HandleAABBCollision(CollidableObject& objA, CollidableObject& objB);

};