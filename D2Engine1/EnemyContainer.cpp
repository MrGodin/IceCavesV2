
#include "EnemyContainer.h"

EnemyContainer::EnemyContainer(Camera& cam)
	:
	ObjContainer(),
	camera(cam)
{

}

void EnemyContainer::Rasterize()
{
	for (UINT c = 0; c < list.size(); c++)
	{
		Enemy* en = (Enemy*)list[c];
		if (camera.PointInViewFrame(en->GetPosition(), {en->GetRadius()*2,en->GetRadius()*2}))
			camera.Rasterize(en->GetDrawable());
		
	}
}
void EnemyContainer::Update(CollidableObject& player, float& dt)
{
	for (UINT c = 0; c < list.size(); c++)
	{
		Enemy* en = (Enemy*)list[c];
		// update objects in larger scope
		if (camera.PointInViewFrame(en->GetPosition(), { 1200.0f,600.0f }))
		{
			en->Update(dt);
			en->GetCollision().MapCollision();
			// limit scope to view plane
			if (camera.PointInViewFrame(en->GetPosition(), { 0.0f,0.0f }))
			{
				if (en->GetCollision().SphericalCollision(player))
				{
					//Remove(c);
				};
			}
			
			
		}
		
	}
}


