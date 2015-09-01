
#include "EnemyContainer.h"
#include "Desc.h"
#include "EnemyCannon.h"
#include "EnemyAmmo.h"

EnemyContainer::EnemyContainer(Camera& cam, StaticAnimationContainer& animations)
	:
	ObjContainer(),
	camera(cam),
	animate(animations)
{

}
void EnemyContainer::createExplosion(float2 pos)
{
	StaticAnimation::AnimationDesc desc;
	desc = GenericDescription::Explosion(pos);
	desc.clip_startpos = float2(0, 64.0f * 5);
	StaticAnimation* anim = animate.Add(desc);
	anim->SetStartEndFrame(0, desc.frames - 1, desc.life_span);
}
void EnemyContainer::Rasterize()
{
	for (UINT c = 0; c < list.size(); c++)
	{
		Sprite* en = (Sprite*)list[c];
		if (camera.PointInViewFrame(en->GetPosition(), {en->GetRadius()*2,en->GetRadius()*2}))
			camera.Rasterize(en->GetDrawable());
		
	}
}
void EnemyContainer::fireAmmo(CollidableObject& obj)
{
	Enemy::EnemyDesc desc;
	
	    bool shot_fired = false;
		float lifespan = 0.0f;
		switch (obj.Type())
		{
			case etLeve1Cannon:
			{
				EnemyCannon* cannon = (EnemyCannon*)&obj;
				shot_fired = cannon->DoFire();
				if (shot_fired)
				{
					float2 vel(275.0f, -120.0f);
					float2 pos = cannon->GetPosition();
					if (cannon->GetDirection().IsLeft())
						vel.x = -vel.x;
					pos += vel * 0.1f;
					desc = GenericDescription::Level1CannonBall(pos, vel, animate.GetImage());
					desc.core.dir = cannon->GetDirection();
					lifespan = 8.0f;
					cannon->Reset();
				}
			}
			break;
			default:
				shot_fired = false;
				break;
		}
		if(shot_fired)
		   Add(new EnemyAmmo(desc,lifespan));
		
	
	
}
bool EnemyContainer::checkAmmoLife(CollidableObject& obj,float &dt)
{
	EnemyAmmo* ammo = (EnemyAmmo*)&obj;
	ammo->Update(dt);
	return ammo->Active();
}
void EnemyContainer::facePlayer(CollidableObject& obj, float2 playerPos)
{
	if (playerPos.x <= obj.GetPosition().x)
		obj.GetState()->OnCtrlDirChange(TDirection::Left());
	else
		obj.GetState()->OnCtrlDirChange(TDirection::Right());
}
void EnemyContainer::Update(CollidableObject& player, float& dt)
{
	for (UINT c = 0; c < list.size(); c++)
	{
		Enemy* en = (Enemy*)list[c];
		if (list[c]->Type() == etAmmo)
		{
			if (!checkAmmoLife(*list[c], dt))
			{
				Remove(c);continue;
			}
		}
		// update objects in larger scope
		if (camera.PointInViewFrame(en->GetPosition(), { 1200.0f,600.0f }))
		{
			if(en->Type() != etAmmo)
			   en->Update(dt);
			en->GetCollision().MapCollision();
			// limit scope to view plane
			if (camera.PointInViewFrame(en->GetPosition(), { 0.0f,0.0f }))
			{
				switch (en->Type())
				{
				
				case etLevel1GuardTank:
					break;
				case etLeve1Cannon:
					facePlayer(*en, player.GetPosition());
					fireAmmo(*en);
				    break;
				}
				if (en)
				{
					if (en->GetCollision().SphericalCollision(player))
					{
						en->SetHitPtsInc(-2.01f);
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
}


