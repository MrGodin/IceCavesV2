#pragma once

#include "Enemy.h"

class GenericDescription
{
public:
	static StaticAnimation::AnimationDesc Explosion(float2& pos)
	{
		StaticAnimation::AnimationDesc desc;

		desc.pos = pos;
		desc.frames = 8;
		desc.startFrame = 0;
		desc.endFrame = 4;
		desc.clipHeight = 64;
		desc.clipWidth = 64;
		desc.drawHeight = 40;
		desc.drawWidth = 40;
		desc.index = 0;
		desc.life_span = 0.45f;
		desc.transparency = 1.0f;
		desc.drawPos = D2D1::RectF(pos.x, pos.y, pos.x + desc.drawWidth, pos.y + desc.drawHeight);
		desc.keep_alive = false;
		return desc;
	}
	static Enemy::EnemyDesc Level1Cannon(float2& pos, ID2D1Bitmap* bmp)
	{
		Enemy::EnemyDesc desc;
		EnemyCore core;
		StaticAnimation::AnimationDesc an;
		Sprite::SpriteDesc sprite;
		D2D1_RECT_F imageRect;

		imageRect = Math::GetImageRectFromIndex(35, bmp, 64, 64);

		sprite.width = sprite.height = 48;

		core.shield_strength = 100.0f;
		core.power = 100.0f;
		core.Type = etLeve1Cannon;
		core.Pos = pos;
		core.Pos.x -= 10;
		core.Vel = float2(0.0f, 0.0f);
		core.mass = 2.75f;
		core.accelX = 0.0f;
		core.maxSpeedX = 0.0f;
		core.maxSpeedY = 200.0f;
		core.dir = TDirection::Right();
		core.traction = 1.988f;
		core.thrust = 0.0f;
		core.anti_gravity = 0.998f;
		core.decayX = 0.999f;
		core.angle = 0.0f;
		core.hit_points = 5.0f;

		an.frames = 2;
		an.bmp = bmp;
		an.clipHeight = an.clipWidth = 64;
		an.drawHeight = an.drawWidth = 48;
		an.keep_alive = true;
		an.life_span = 0.5f;
		an.clipOffsetW = an.clipOffsetH = 8;
		an.do_animate = false;
		an.index = 0;
		an.clip_startpos = float2(imageRect.left, imageRect.top);
		an.pos = core.Pos;

		desc.core = core;
		sprite.animateDesc = an;
		desc.sprite = sprite;
		return desc;
	}
	static Enemy::EnemyDesc Level1GuardTank(float2& pos, ID2D1Bitmap* bmp)
	{
		Enemy::EnemyDesc desc;
		EnemyCore core;
		StaticAnimation::AnimationDesc an;
		Sprite::SpriteDesc sprite;
		D2D1_RECT_F imageRect;

		imageRect = Math::GetImageRectFromIndex(37, bmp, 64, 64);

		sprite.width = sprite.height = 48;

		core.shield_strength = 100.0f;
		core.power = 100.0f;
		core.Type = etLevel1GuardTank;
		core.Pos = pos;
		core.Pos.x -= 10;
		core.Vel = float2(10.0f, 12.0f);
		core.mass = 2.75f;
		core.accelX = 1.0f;
		core.maxSpeedX = 176.0f;
		core.maxSpeedY = 200.0f;
		core.dir = TDirection::Right();
		core.traction = 0.988f;
		core.thrust = 3.0f;
		core.anti_gravity = 0.998f;
		core.decayX = 0.939f;
		core.angle = 0.0f;
		core.hit_points = 6.0f;

		an.frames = 2;
		an.bmp = bmp;
		an.clipHeight = an.clipWidth = 64;
		an.drawHeight = an.drawWidth = 48;
		an.keep_alive = true;
		an.life_span = 0.5f;
		an.clipOffsetW = an.clipOffsetH = 8;
		an.do_animate = false;
		an.index = 0;
		an.clip_startpos = float2(imageRect.left, imageRect.top);
		an.pos = core.Pos;

		desc.core = core;
		sprite.animateDesc = an;
		desc.sprite = sprite;
		return desc;
	}
	static Enemy::EnemyDesc Level1Roamer(float2& pos,ID2D1Bitmap* bmp)
	{
		Enemy::EnemyDesc desc;
		EnemyCore core;
		StaticAnimation::AnimationDesc an;
		Sprite::SpriteDesc sprite;
		D2D1_RECT_F imageRect;

		imageRect = Math::GetImageRectFromIndex(27, bmp, 64, 64);
		
		sprite.width = sprite.height = 48;

		core.shield_strength = 60.0f;
		core.power = 100.0f;
		core.Type = etLevel1Roamer;
		core.Pos = pos;
		core.Vel = float2(1.0f, 1.0f);
		core.mass = 1.75f;
		core.accelX = 2.0f;
		core.maxSpeedX = 126.0f;
		core.maxSpeedY = 326.0f;
		core.dir = TDirection::Right();
		core.traction = 0.988f;
		core.thrust = 22.0f;
		core.anti_gravity = 0.998f;
		core.decayX = 0.989f;
		core.angle = 0.0f;
		core.hit_points = 4.0f;

		an.frames = 2;
		an.bmp = bmp;
		an.clipHeight = an.clipWidth = 64;
		an.drawHeight = an.drawWidth = 48;
		an.keep_alive = true;
		an.life_span = 0.5f;
		an.clipOffsetW = an.clipOffsetH = 8;
		an.do_animate = true;
		an.index = 0;
		an.clip_startpos = float2(imageRect.left, imageRect.top);
		an.pos = core.Pos;
		
		desc.core = core;
		sprite.animateDesc = an;
		desc.sprite = sprite;
		return desc;
	}
	static Enemy::EnemyDesc Level1CannonBall(float2& pos, float2& vel, ID2D1Bitmap* bmp)
	{
		Enemy::EnemyDesc desc;
		EnemyCore core;
		StaticAnimation::AnimationDesc an;
		Sprite::SpriteDesc sprite;
		D2D1_RECT_F imageRect;

		imageRect = Math::GetImageRectFromIndex(21, bmp, 64, 64);

		sprite.width = sprite.height = 32;

		core.shield_strength = 60.0f;
		core.power = 100.0f;
		core.Type = etAmmo;
		core.Pos = pos;
		core.Vel = vel;
		core.mass = 1.75f;
		core.accelX = 2.0f;
		core.maxSpeedX = 226.0f;
		core.maxSpeedY = 326.0f;
		core.dir = TDirection::Right();
		core.traction = 0.988f;
		core.thrust = 22.0f;
		core.anti_gravity = 0.998f;
		core.decayX = 0.989f;
		core.decayY = 90.0f;
		core.angle = 0.0f;
		core.hit_points = 0.0f;

		an.frames = 1;
		an.bmp = bmp;
		an.clipHeight = an.clipWidth = 64;
		an.drawHeight = an.drawWidth = 32;
		an.keep_alive = true;
		an.life_span = 0.5f;
		an.clipOffsetW = an.clipOffsetH = 0;
		an.do_animate = true;
		an.index = 0;
		an.clip_startpos = float2(imageRect.left, imageRect.top);
		an.pos = core.Pos;

		desc.core = core;
		sprite.animateDesc = an;
		desc.sprite = sprite;
		return desc;
	}
};