

#include "EnemyPatrol.h"


void EnemyPatrol::Update(float dt)
{
	pCore.thrust += 0.15f;
	pCore.Vel.x += pCore.dir.Translate(pCore.accelX);
	// confine to either - or + maxSpeed
	pCore.Vel.x = __min(pCore.maxSpeedX, pCore.Vel.x);
	pCore.Vel.x = __max(-pCore.maxSpeedX, pCore.Vel.x);
	pCore.Pos += pCore.Vel * dt;
	

}


void EnemyPatrol::OnUnsupported()
{
	pCore.Pos += -pCore.Vel * 2.0f * (1.0f / 60.0f) ;
	pCore.Vel = -pCore.Vel;
	pCore.dir.Reverse();
}
void EnemyPatrol::OnCollision(const RectF& rect, const RectF& FRect)
{
	pCore.Vel.x > 0.0f ? pCore.Pos.x -= FRect.right - rect.left : pCore.Pos.x += rect.right - FRect.left;
	pCore.Vel.x = -(pCore.Vel.x * pCore.decayX / 2);
	pCore.dir.Reverse();
}
void EnemyPatrol::OnCtrlDirChange(TDirection& d)
{
	pCore.dir = d;
}