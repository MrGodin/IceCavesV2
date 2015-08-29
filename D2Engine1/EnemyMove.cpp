#include "EnemyMove.h"

#include "EnemyJump.h"


void EnemyMove::Update(float dt)
{
	pCore.thrust += 0.15f;
	pCore.Vel.x += pCore.dir.Translate(pCore.accelX);
	// confine to either - or + maxSpeed
	pCore.Vel.x = __min(pCore.maxSpeedX, pCore.Vel.x);
	pCore.Vel.x = __max(-pCore.maxSpeedX, pCore.Vel.x);
	pCore.Pos += pCore.Vel * dt;
	if (ETimer.Update(dt))
	{
		Transition(new EnemyJump(pCore, true, false,Math::RandFloat(-800.0f,-200.0f)));
		return;
	}

}


void EnemyMove::OnUnsupported()
{
	Transition(new EnemyJump(pCore, false, false));
}
void EnemyMove::OnCollision(const RectF& rect, const RectF& FRect)
{
	pCore.Vel.x > 0.0f ? pCore.Pos.x -= FRect.right - rect.left : pCore.Pos.x += rect.right - FRect.left;
	pCore.Vel.x = -(pCore.Vel.x * pCore.decayX / 2);
	pCore.dir.Reverse();
}