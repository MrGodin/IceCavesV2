#pragma once

#include "Enemy.h"
#include "EnemyAmmoMove.h"
class EnemyAmmo : public Enemy
{
	_EventTimer timer;
public:
	EnemyAmmo(EnemyDesc& desc,float& lifespan)
		:
		Enemy(desc),
		timer(lifespan)
	{
		core.state = new EnemyAmmoMove(core);
	}
	virtual ~EnemyAmmo() {}
	virtual bool Active()override { return core.active; }
	virtual void Update(float dt)override
	{
		core.state->Update(dt);
		animation.SetPos(core.Pos);
		animation.AngleInc(2 * Math::sgn(core.Vel.x));
		core.active = !timer.Update(dt);
		
	}
};