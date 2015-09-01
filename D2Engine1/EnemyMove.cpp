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
	if (pCore.doUnsupported)
	{
		if (ETimer.Update(dt))
		{
			Transition(new EnemyJump(pCore, true, false, Math::RandFloat(-800.0f, -200.0f)));
			return;
		}
	}

}


void EnemyMove::OnUnsupported()
{
	if (pCore.doUnsupported)
	{
		Transition(new EnemyJump(pCore, false, false));
	}
	else 
	{
		if (pCore.Vel.y == 0.0f)
		{
			pCore.Pos.x += -pCore.Vel.x * (1.0f / 60.0f) * 2.0f;
			pCore.Vel.x = -pCore.Vel.x;
			pCore.dir.Reverse();
		}
		else
		{
			Transition(new EnemyJump(pCore, false, false));
		}
		
	}
}
void EnemyMove::OnCollision(const RectF& rect, const RectF& FRect)
{
	pCore.Vel.x > 0.0f ? pCore.Pos.x -= FRect.right - rect.left : pCore.Pos.x += rect.right - FRect.left;
	pCore.Vel.x = -(pCore.Vel.x * pCore.decayX / 2);
	pCore.dir.Reverse();
}