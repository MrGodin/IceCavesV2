
#include "EnemyContainer.h"

EnemyContainer::EnemyContainer(Camera& cam, StaticAnimationContainer& animations)
	:
	ObjContainer(),
	camera(cam),
	animate(animations)
{

}
void EnemyContainer::createExplosion(float2 pos)
{
	StaticAnimation::StaticAnimationDesc desc;
	desc.pos = pos;
	desc.clipHeight = 64;
	desc.clipWidth = 64;
	desc.clip_startpos = float2(0, 64.0f * 5);
	desc.frames = 8;
	desc.index = 0;
	desc.life_span = 0.45f;
	desc.transparency = 1.0f;
	desc.drawPos = D2D1::RectF(pos.x - 8, pos.y - 8, pos.x + 64 / 2, pos.y + 64 / 2);
	animate.Add(desc);
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
					en->SetHitPtsInc(-2.0f);
					if (en->GetHitPts() < 0.0f)
					{
						createExplosion(en->GetPosition());
						Remove(c);
					}
				};
			}
			
			
		}
		
	}
}


