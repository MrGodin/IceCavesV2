#include "EnemyJump.h"
#include "EnemyMove.h"

void EnemyJump::Update(float dt)
{

	if (isThrusting)
	{

		pCore.Vel.y += -(pCore.thrust - pCore.anti_gravity);

	}
	else
	{
		pCore.Vel.y += gravity;//  *dt;

	}
	if (isMoving)
	{
		pCore.Vel.x += pCore.dir.Translate(pCore.accelX);

	}
	else
	{
		pCore.Vel.x *= pCore.decayX;
	}
	// confine to either - or + maxSpeed
	pCore.Vel.y = __min(pCore.maxSpeedY, pCore.Vel.y);
	pCore.Vel.y = __max(-pCore.maxSpeedY, pCore.Vel.y);
	pCore.Vel.x = __min(pCore.maxSpeedX, pCore.Vel.x);
	pCore.Vel.x = __max(-pCore.maxSpeedX, pCore.Vel.x);


	pCore.Pos += pCore.Vel * dt;
}
void EnemyJump::OnCtrlJumpPress()
{

	pCore.thrust -= 0.45f;
	if (pCore.thrust < 0.0f)
		pCore.thrust = 0.0f;
}
void EnemyJump::OnCtrlDirRelease()
{
	isMoving = false;
}
void EnemyJump::OnCtrlDirChange(TDirection& d)
{
	isMoving = true;
	if (d != pCore.dir)
		pCore.dir = d;
}
void EnemyJump::OnCtrlJumpRelease()
{
	isThrusting = false;
}


void EnemyJump::OnCollision(const RectF& rect, const RectF& FRect)
{

	if (pCore.Vel.x > 0.0f)
	{

		if (pCore.Vel.y > 0.0f)
		{

			float px = FRect.right - rect.left;
			float py = FRect.bottom - rect.top;
			if (pCore.Vel.y* px > pCore.Vel.x * py)
			{
				// top

				pCore.Pos.y -= py;
				Transition(new EnemyMove(pCore));
				
			}
			else
			{
				// side
				pCore.Vel.x = -(pCore.Vel.x * pCore.decayX / 2);
				pCore.Pos.x -= px;

			}
		}
		else //pCore.Vel.y > 0.0f
		{
			float px = FRect.right - rect.left;
			float py = rect.bottom - FRect.top;
			if ((-pCore.Vel.y)* px > pCore.Vel.x * py)
			{
				// top
				pCore.Vel.y = 2.0f;
				pCore.Pos.y += py;


			}
			else
			{
				// side
				pCore.Vel.x = -(pCore.Vel.x * pCore.decayX / 2);
				pCore.Pos.x -= px;

			}
		}
	}
	else///pCore.Vel.x > 0.0f
	{

		if (pCore.Vel.y > 0.0f)
		{

			float px = rect.right - FRect.left;
			float py = FRect.bottom - rect.top;
			if (pCore.Vel.y* px > (-pCore.Vel.x) * py)
			{
				// top

				pCore.Pos.y -= py;

				Transition(new EnemyMove(pCore));
			}
			else
			{
				// side
				pCore.Vel.x = -(pCore.Vel.x * pCore.decayX / 2);
				pCore.Pos.x += px;

			}
		}
		else //pCore.Vel.y > 0.0f
		{
			float px = rect.right - FRect.left;
			float py = rect.bottom - FRect.top;
			if ((-pCore.Vel.y)* px > (-pCore.Vel.x) * py)
			{
				// top
				pCore.Vel.y = 0.0f;
				pCore.Pos.y += py;
				pCore.Vel.y = 2.0f;

				isThrusting = false;


			}
			else
			{
				// side
				pCore.Vel.x = -(pCore.Vel.x * pCore.decayX / 2);
				pCore.Pos.x += px;

			}
		}
	}
}