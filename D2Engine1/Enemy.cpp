

#include "Enemy.h"
#include "EnemyJump.h"
#include "EnemyPatrol.h"
#include "EnemyMove.h"
Enemy::Enemy(EnemyDesc& desc)
:
Sprite(desc.sprite),
core(desc.core)
{
	
	type = (UINT)core.Type;
	switch (core.Type)
	{
	case etLevel1Roamer:
		core.doUnsupported = true;
		core.state = new EnemyJump(core, false, false, 12.0f);

		break;
	case etLevel1GuardTank:
		core.doUnsupported = false;
		
		core.state =  new EnemyJump(core, false, false,12.0f);;
	break;
	case etLeve1Cannon:
		core.doUnsupported = false;

		core.state = new EnemyJump(core, false, false, 12.0f);;
		break;
	default:
		assert(type < etNumbTypes);
	break;
	}

}


Enemy::~Enemy()
{

	SAFE_DELETE(core.state);
}
void Enemy::Update(float dt)
{
	core.state->Update(dt);
	animation.SetPos(core.Pos);
	animation.Update(dt);
	if(!animation.Animate())
	  core.dir.IsLeft() ? SetImageIndex(1) : SetImageIndex(0);

	//pos = core.Pos;
}
D2D_RECT_F Enemy::GetDrawSize()
{
	float2 p(core.Pos.x, core.Pos.y);
	return D2D1::RectF(p.x, p.y, p.x + width, p.y + height);
}

RectF Enemy::GetAABB()
{
	float2 p(core.Pos.x, core.Pos.y);
	return RectF(p.y, p.x, p.x + width, p.y + height);
};
float2  Enemy::GetVelocity()
{
	return core.Vel;
};
float2  Enemy::GetPosition()
{
	return core.Pos;
};
void   Enemy::SetVelocity(const float2 v)
{
	core.Vel = v;
};
void   Enemy::SetPosition(const float2 p)
{
	core.Pos = p;
};
float  Enemy::GetRadius()
{
	return __max(width * 0.5f, height * 0.5f);
};
float  Enemy::GetMass()
{
	return core.mass;
};
float2  Enemy::GetCenter()
{
	return float2(GetAABB().left + (width * 0.5f), GetAABB().top + (height* 0.5f));
};
void   Enemy::Rebound(const float2 normal)
{};
//=======================================================
ObjectState* Enemy::GetState()
{
	return core.state;
}