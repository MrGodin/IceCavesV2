
#include "Player.h"


Player::Player(float2 pos, float width, float height, ID2D1Bitmap *bmp, D2D1_RECT_F cliprect)
:
Sprite(pos,width,height,bmp,cliprect)
{
	core.pos = pos;
	core.vel = float2(12.5f, 0.0f);
}
//=======================================================
void Player::Update(float dt)
{
	//core.state->Update(dt);
	core.pos += core.vel * dt;
	
}
D2D_RECT_F Player::GetDrawSize() 
{ 
	return D2D1::RectF(core.pos.x, core.pos.y,core.pos.x +width ,core.pos.y + height); 
}
 
RectF Player::GetAABB()
{
	return RectF(core.pos.y, core.pos.x, core.pos.x + width, core.pos.y + height);
};
float2  Player::GetVelocity()
{
	return core.vel;
};
float2  Player::GetPosition()
{
	return core.pos;
};
void   Player::SetVelocity(const float2 v)
{
	core.vel = v;
};
void   Player::SetPosition(const float2 p)
{
	core.pos = p;
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
	return float2(core.pos.x + (width * 0.5f), core.pos.y + (height * 0.5f));
};
void   Player::Rebound(const float2 normal)
{};
PlayerCore* Player::GetCore()
{
	return &core;
};