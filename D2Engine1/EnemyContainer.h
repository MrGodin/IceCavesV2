#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Camera.h"
#include "ObjContainer.h"
#include "StaticAnimationContainer.h"

class EnemyContainer : public ObjContainer
{
private:
	Camera& camera;
	StaticAnimationContainer& animate;
	void createExplosion(float2 pos);
public:
	
	EnemyContainer(Camera& cam, StaticAnimationContainer& animations);
	
	virtual void Rasterize();
	virtual void Update(CollidableObject& player, float& dt);
	
};