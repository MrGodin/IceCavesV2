#include "EnemyCannon.h"

EnemyCannon::EnemyCannon(EnemyDesc& desc,float& delay)
	:
	Enemy(desc),
	timer_delay(delay)
{

}
void EnemyCannon::fireBall()
{

}
void EnemyCannon::Update(float dt)
{
	core.state->Update(dt);
	animation.SetPos(core.Pos);
	animation.Update(dt);
	if (!animation.Animate())
		core.dir.IsLeft() ? SetImageIndex(1) : SetImageIndex(0);

	can_fire = timer.Update(dt);
	
}