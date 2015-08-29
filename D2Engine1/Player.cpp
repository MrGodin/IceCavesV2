
#include "Player.h"
#include "PlayerJump.h"
#include "PlayerMove.h"

Player::Player(float2 pos, float width, float height, ID2D1Bitmap *bmp, D2D1_RECT_F cliprect)
:
Sprite(pos,width,height,bmp,cliprect)
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
	core.mass = 2.0f;
	core.decayX = 0.989f;
	core.angle = 0.0f;
	core.state = new PlayerMove(core);
}
//=======================================================
ObjectState* Player::GetState()
{
	return core.state;
}
Player::~Player()
{
	
	SAFE_DELETE(core.state);
}
void Player::Update(float dt)
{
	core.state->Update(dt);
	pos = core.Pos;
}
D2D_RECT_F Player::GetDrawSize() 
{ 
	float2 p(core.Pos.x  , core.Pos.y  );
	return D2D1::RectF(p.x , p.y,p.x + width ,p.y + height); 
}
 
RectF Player::GetAABB()
{
	float2 p(core.Pos.x, core.Pos.y );
	return RectF(p.y, p.x, p.x + width , p.y + height  );
};
float2  Player::GetVelocity()
{
	return core.Vel;
};
float2  Player::GetPosition()
{
	return core.Pos;
};
void   Player::SetVelocity(const float2 v)
{
	core.Vel = v;
};
void   Player::SetPosition(const float2 p)
{
	core.Pos = p;
};
float  Player::GetRadius()
{
	return __max(width * 0.5f, height * 0.5f);
};
float  Player::GetMass()
{
	return core.mass;
};
float2  Player::GetCenter()
{
	return float2(GetAABB().left + (width * 0.5f), GetAABB().top + (height* 0.5f));
};
void   Player::Rebound(const float2 normal)
{
	core.Vel -= normal *(core.Vel * normal) * 2.0f;
};
