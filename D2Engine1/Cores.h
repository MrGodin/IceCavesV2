#pragma once
#include "UtilsD2.h"
class ObjectCore
{
public:
	float radius;
	float2 pos;
	float2 vel;
	
	
	

};
class PlayerCore : public ObjectCore
{
public:
	float mass;
	float vert_accel;
	float horiz_accel;
	float max_velX;
	float max_velY;
	class PlayerState* state = NULL;
};