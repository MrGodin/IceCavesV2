
#pragma once

#include "UtilsD2.h"

static const float gravity = 4.01f;

class ObjectCore
{
public:
	ObjectCore(){}
	TDirection dir;
	Vec2F Pos;
	Vec2F Vel;
	UINT  level;
	UINT  tokens;
	float accelX;
	float accelY;
	float decayX;
	float decayY;
	float maxSpeedX;
	float maxSpeedY;
	float thrust;
	float traction;
	float bounce_absorb;
	float anti_gravity;
	float shield_strength;
	float hit_points;
	float power;
	float mass;
	int way_point;
	float angle;
	class ObjectState* state = NULL;
	
};
class PlayerCore 
{
public:
	PlayerCore(){}
	TDirection dir;
	Vec2F Pos;
	Vec2F Vel;
	UINT  level;
	UINT  tokens;
	float accelX;
	float accelY;
	float decayX;
	float decayY;
	float maxSpeedX;
	float maxSpeedY;
	float thrust;
	float traction;
	float bounce_absorb;
	float anti_gravity;
	float shield_strength;
	float hit_points;
	float power;
	float mass;
	int way_point;
	float angle;
	class ObjectState* state = NULL;
	
};

class EnemyCore
{
public:
	EnemyCore(){}
	TDirection dir;
	Vec2F Pos;
	Vec2F Vel;
	float accelX;
	float accelY;
	float thrust;
	float traction;
	float bounce_absorb;
	float anti_gravity;
	float shield_strength;
	float hit_points;
	float power;
	float mass;
	float angle;
	float decayX;
	float decayY;
	float maxSpeedX;
	float maxSpeedY;
	class ObjectState* state = NULL;

};