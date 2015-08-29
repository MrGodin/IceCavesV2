

#include "Enemy.h"
#include "EnemyJump.h"
Enemy::Enemy(float2 pos, float width, float height, ID2D1Bitmap *bmp, D2D1_RECT_F cliprect)
	:
	Sprite(pos, width, height, bmp, cliprect)
{
	core.Pos = pos;
	core.Vel.x = 0.0f;
	core.accelX = 2.0f;
	core.maxSpeedX = 226.0f;
	core.maxSpeedY = 326.0f;
	core.dir = TDirection::Right();
	core.traction = 0.988f;
	core.thrust = 12.0f;
	core.anti_gravity = 0.998f;
	core.mass = 0.5f;
	core.decayX = 0.989f;
	core.angle = 0.0f;
	core.state = new EnemyJump(core,false,false);
}

Enemy::~Enemy()
{

	SAFE_DELETE(core.state);
}
void Enemy::Update(float dt)
{
	core.state->Update(dt);
	pos = core.Pos;
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