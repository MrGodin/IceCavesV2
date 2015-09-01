
#include "EnemyAmmoMove.h"
void EnemyAmmoMove::Update(float dt)
{

		pCore.Vel.y += pCore.decayY * dt;
		pCore.Vel.x *= 0.9999f;// pCore.dir.Translate(0.9999f);

	
	// confine to either - or + maxSpeed
	pCore.Vel.y = __min(pCore.maxSpeedY, pCore.Vel.y);
	pCore.Vel.y = __max(-pCore.maxSpeedY, pCore.Vel.y);
	pCore.Vel.x = __min(pCore.maxSpeedX, pCore.Vel.x);
	pCore.Vel.x = __max(-pCore.maxSpeedX, pCore.Vel.x);


	pCore.Pos += pCore.Vel * dt;
}
void EnemyAmmoMove::OnCtrlJumpPress()
{

	pCore.thrust -= 0.45f;
	if (pCore.thrust < 0.0f)
		pCore.thrust = 0.0f;
}
void EnemyAmmoMove::OnCtrlDirRelease()
{
	
}
void EnemyAmmoMove::OnCtrlDirChange(TDirection& d)
{
	
	if (d != pCore.dir)
		pCore.dir = d;
}
void EnemyAmmoMove::OnCtrlJumpRelease()
{
	
}


void EnemyAmmoMove::OnCollision(const RectF& rect, const RectF& FRect)
{
	//pCore.active = false;
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
			

			}
			else
			{
				// side
				
				pCore.Pos.x -= px;
				pCore.Vel.x = -pCore.Vel.x;
				pCore.dir.Reverse();

			}
		}
		else //pCore.Vel.y > 0.0f
		{
			float px = FRect.right - rect.left;
			float py = rect.bottom - FRect.top;
			if ((-pCore.Vel.y)* px > pCore.Vel.x * py)
			{
				// top
				
				pCore.Pos.y += py;


			}
			else
			{
				// side
				
				pCore.Pos.x -= px;
				pCore.Vel.x = -pCore.Vel.x;
				pCore.dir.Reverse();

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

				
			}
			else
			{
				// side
				pCore.Vel.x = -pCore.Vel.x;
				pCore.dir.Reverse();
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
				


			}
			else
			{
				// side
				pCore.Vel.x = -pCore.Vel.x;
				pCore.dir.Reverse();
				pCore.Pos.x += px;

			}
		}
	}
}