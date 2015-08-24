
#include "Collisions.h"
#include "MapTile.h"
#include "TileMap.h"
#include "ObjectState.h"
bool Collision::HandleSphericalObjectCollision(CollidableObject& objA, CollidableObject& objB)
{


	float xd = objA.GetCenter().x - objB.GetCenter().x;
	float yd = objA.GetCenter().y - objB.GetCenter().y;

	float sumRadius = objA.GetRadius() + objB.GetRadius();
	float sqrRadius = sumRadius * sumRadius;

	float distSqr = (xd * xd) + (yd * yd);

	if (distSqr <= sqrRadius)
	{
		float2 delta = objA.GetCenter() - objB.GetCenter();
		float d = V2Math::len(delta);
		// minimum translation distance to push balls apart after intersecting

		float2 mtd = delta * (objA.GetRadius() + objB.GetRadius() - d) / d;


		// resolve intersection --
		// inverse mass quantities
		float im1 = 1.0f / objA.GetMass();
		float im2 = 1.0f / objB.GetMass();


		// impact speed
		float2 v = (objA.GetVelocity() - objB.GetVelocity());
		float2 mtdNorm = V2Math::norm(mtd);
		float vn = v.x*mtdNorm.x + v.y*mtdNorm.y;

		// sphere intersecting but moving away from each other already
		if (vn > 0.0f) return false;

		//// collision impulse
		float i = (-(1.0f + 1.25f) * vn) / (im1 + im2);
		float2 impulse = mtd * i;

		//// change in momentum
		float2 velocity = objA.GetVelocity() + impulse * im1;
		float2 velocity2 = objB.GetVelocity() - impulse * im2;

		// cap velocity ? .... 
		velocity.x = max(-120.0f, velocity.x);
		velocity.x = min(120.0f, velocity.x);
		velocity.y = max(-120.0f, velocity.y);
		velocity.y = min(120.0f, velocity.y);

		velocity2.x = max(-120.0f, velocity2.x);
		velocity2.x = min(120.0f, velocity2.x);
		velocity2.y = max(-120.0f, velocity2.y);
		velocity2.y = min(120.0f, velocity2.y);



		objA.SetVelocity(velocity);
		objB.SetVelocity(velocity2);
		return true;


	}

	return false;
}

bool Collision::HandleSingleMapTileCollision(CollidableObject& objA, RectF& tileRect)
{
	float2 vel = objA.GetVelocity();
	RectF objRect(objA.GetAABB().top, objA.GetAABB().left, objA.GetAABB().right, objA.GetAABB().bottom);
	
	if (vel.x > 0.0f)
	{
		if (vel.y < 0.0f)
		{
			for (int iy = MapTile::GetIndexYBiasTop(objRect.bottom), iyEnd = MapTile::GetIndexYBiasBottom(objRect.top);
			iy >= iyEnd; iy--)
			{
				for (int ix = MapTile::GetIndexXBiasRight(objRect.left), ixEnd = MapTile::GetIndexXBiasLeft(objRect.right);
				ix <= ixEnd; ix++)
				{

					MapTile* tile = TileMap::GetTile(ix, iy);
					if (tile)
					{
						if (tile->Solid())
						{
							tileRect = MapTile::GetRectIndexed(ix, iy);
							return true;
						}
					}
				}
			}
		}
		else
		{
			for (int iy = MapTile::GetIndexYBiasBottom(objRect.top), iyEnd = MapTile::GetIndexYBiasTop(objRect.bottom);
			iy <= iyEnd; iy++)
			{
				for (int ix = MapTile::GetIndexXBiasRight(objRect.left), ixEnd = MapTile::GetIndexXBiasLeft(objRect.right);
				ix <= ixEnd; ix++)
				{
					MapTile* tile = TileMap::GetTile(ix, iy);
					if (tile)
					{
						if (tile->Solid())
						{
							tileRect = MapTile::GetRectIndexed(ix, iy);
							return true;
						}
					}
				}
			}
		}
	}
	else
	{
		if (vel.y < 0.0f)
		{
			for (int iy = MapTile::GetIndexYBiasTop(objRect.bottom), iyEnd = MapTile::GetIndexYBiasBottom(objRect.top);
			iy >= iyEnd; iy--)
			{
				for (int ix = MapTile::GetIndexXBiasLeft(objRect.right), ixEnd = MapTile::GetIndexXBiasRight(objRect.left);
				ix >= ixEnd; ix--)
				{
					MapTile* tile = TileMap::GetTile(ix, iy);
					if (tile)
					{
						if (tile->Solid())
						{
							tileRect = MapTile::GetRectIndexed(ix, iy);
    						return true;
						}
					}
				}
			}
		}
		else
		{
			for (int iy = MapTile::GetIndexYBiasBottom(objRect.top), iyEnd = MapTile::GetIndexYBiasTop(objRect.bottom);
			iy <= iyEnd; iy++)
			{
				for (int ix = MapTile::GetIndexXBiasLeft(objRect.right), ixEnd = MapTile::GetIndexXBiasRight(objRect.left);
				ix >= ixEnd; ix--)
				{
					MapTile* tile = TileMap::GetTile(ix, iy);
					if (tile)
					{
						if (tile->Solid())
						{
							tileRect = MapTile::GetRectIndexed(ix, iy);
							return true;
						}
					}
				}
			}
		}
		

	};
	return false;
}
void Collision::HandleMapCollision(CollidableObject& objA)
{
	RectF tileRect;
	RectF objRect(objA.GetAABB().top, objA.GetAABB().left, objA.GetAABB().right, objA.GetAABB().bottom);

	while (HandleSingleMapTileCollision(objA,tileRect))
	{
		objA.GetCore()->state->OnCollision(tileRect, objRect);
	}
}